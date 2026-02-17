#include "../Include/Level1.h"
#include "../Include/Renderer.h"

Level1::Level1() : Level(1) {
    m_backgroundColor = {128, 128, 128, 255}; // Grey
}

Level1::~Level1() {
}

void Level1::Initialize() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> speedDist(80.0f, 100.0f);

    // Spawn 10 warriors
    for (int i = 0; i < 10; i++) {
        float yPos = 10.0f + (i * 100.0f);  // Y: 10, 110, 210, ..., 910
        float xPos = -100.0f;  // Start off-screen left
        float speed = speedDist(gen);  // 80-100 px/s
        float animSpeed = 4.8f + ((speed - 80.0f) / 20.0f) * 1.2f;  // 4.8-6.0 fps

        Warrior* warrior = Warrior::Pool->GetResource();
        warrior->Initialize(xPos, yPos, speed, animSpeed, 1.8f);
        m_warriors.push_back(warrior);
    }

    m_gameTime = 0.0f;
    m_autoSaved = false;
}

void Level1::Update(float deltaTime) {
    m_gameTime += deltaTime;

    // Update all warriors
    for (Warrior* warrior : m_warriors) {
        warrior->Update(deltaTime);
    }

    // Check auto-save
    CheckAutoSave();
}

void Level1::Render(Renderer* renderer) {
    // Render all warriors
    for (Warrior* warrior : m_warriors) {
        warrior->Render(renderer);
    }
}

bool Level1::ShouldTransition() const {
    // Transition when first warrior exits screen
    if (!m_warriors.empty() && m_warriors[0]->GetX() > 1920.0f) {
        return true;
    }
    return false;
}

void Level1::CheckAutoSave() {
    if (m_gameTime >= 5.0f && !m_autoSaved) {
        SaveToFile("Level1.bin");
        
        // Reload to verify serialization
        std::ifstream file("Level1.bin", std::ios::binary);
        if (file.is_open()) {
            Level1* reloaded = new Level1();
            reloaded->Deserialize(file);
            file.close();
            
            // Replace current state with reloaded
            m_warriors = reloaded->GetWarriors();
            m_gameTime = reloaded->GetGameTime();
            m_autoSaved = true;
            
            delete reloaded;
        }
    }
}

void Level1::Serialize(std::ostream& stream) {
    Level::Serialize(stream);
}

void Level1::Deserialize(std::istream& stream) {
    Level::Deserialize(stream);
}
