#include "../Include/Level2.h"
#include "../Include/Renderer.h"

Level2::Level2(std::vector<Warrior*> warriors) : Level(2) {
    m_backgroundColor = {0, 128, 0, 255}; // Light Green
    m_warriors = warriors;
}

Level2::~Level2() {
}

void Level2::Initialize() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> speedDist(80.0f, 100.0f);

    // Spawn 10 rocks
    for (int i = 0; i < 10; i++) {
        float xPos = 50.0f + (i * 100.0f);  // X: 50, 150, 250, ..., 950
        float yPos = -100.0f;  // Start off-screen top
        float speed = speedDist(gen);  // 80-100 px/s
        float animSpeed = 4.8f + ((speed - 80.0f) / 20.0f) * 1.2f;  // 4.8-6.0 fps

        Rock* rock = Rock::Pool->GetResource();
        rock->Initialize(xPos, yPos, speed, animSpeed, 1.0f);
        m_rocks.push_back(rock);
    }

    m_gameTime = 0.0f;
    m_autoSaved = false;
}

void Level2::Update(float deltaTime) {
    m_gameTime += deltaTime;

    // Update all warriors
    for (Warrior* warrior : m_warriors) {
        warrior->Update(deltaTime);
    }

    // Update all rocks
    for (Rock* rock : m_rocks) {
        rock->Update(deltaTime);
    }

    // Check collisions
    CheckCollisions();

    // Remove inactive rocks
    m_rocks.erase(std::remove_if(m_rocks.begin(), m_rocks.end(),
        [](Rock* r) { return !r->IsActive(); }), m_rocks.end());

    // Remove dead warriors (after death animation completes)
    m_warriors.erase(std::remove_if(m_warriors.begin(), m_warriors.end(),
        [](Warrior* w) { return w->IsDead(); }), m_warriors.end());

    // Check auto-save
    CheckAutoSave();
}

void Level2::Render(Renderer* renderer) {
    // Render all warriors
    for (Warrior* warrior : m_warriors) {
        warrior->Render(renderer);
    }

    // Render all rocks
    for (Rock* rock : m_rocks) {
        rock->Render(renderer);
    }
}

bool Level2::ShouldQuit() const {
    // Condition 1: First warrior exits screen
    if (!m_warriors.empty() && m_warriors[0]->GetX() > 1920.0f) {
        return true;
    }

    // Condition 2: All warriors dead
    bool allDead = true;
    for (Warrior* w : m_warriors) {
        if (w->IsAlive() || w->IsDying()) {
            allDead = false;
            break;
        }
    }
    return allDead;
}

bool Level2::CheckAABBCollision(Warrior* w, Rock* r) {
    float w_left = w->GetX();
    float w_right = w->GetX() + w->GetWidth();
    float w_top = w->GetY();
    float w_bottom = w->GetY() + w->GetHeight();

    float r_left = r->GetX();
    float r_right = r->GetX() + r->GetWidth();
    float r_top = r->GetY();
    float r_bottom = r->GetY() + r->GetHeight();

    return (w_left < r_right && w_right > r_left &&
            w_top < r_bottom && w_bottom > r_top);
}

void Level2::CheckCollisions() {
    for (Rock* rock : m_rocks) {
        if (!rock->IsActive()) continue;

        for (Warrior* warrior : m_warriors) {
            if (warrior->IsAlive() && CheckAABBCollision(warrior, rock)) {
                warrior->StartDeathAnimation();
                rock->SetActive(false);
                break;  // Rock can only hit one warrior
            }
        }
    }
}

void Level2::CheckAutoSave() {
    if (m_gameTime >= 5.0f && !m_autoSaved) {
        SaveToFile("Level2.bin");
        
        // Reload to verify serialization
        std::ifstream file("Level2.bin", std::ios::binary);
        if (file.is_open()) {
            // Don't actually reload in Level2, just mark as saved
            file.close();
            m_autoSaved = true;
        }
    }
}

void Level2::Serialize(std::ostream& stream) {
    Level::Serialize(stream);

    // Serialize rocks
    size_t rockCount = m_rocks.size();
    stream.write(reinterpret_cast<const char*>(&rockCount), sizeof(size_t));

    for (Rock* rock : m_rocks) {
        rock->Serialize(stream);
    }
}

void Level2::Deserialize(std::istream& stream) {
    Level::Deserialize(stream);

    // Deserialize rocks
    size_t rockCount;
    stream.read(reinterpret_cast<char*>(&rockCount), sizeof(size_t));

    m_rocks.clear();
    for (size_t i = 0; i < rockCount; ++i) {
        Rock* rock = Rock::Pool->GetResource();
        rock->Deserialize(stream);
        m_rocks.push_back(rock);
    }
}
