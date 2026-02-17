#include "../Include/Warrior.h"
#include "../Include/Renderer.h"

ObjectPool<Warrior>* Warrior::Pool = nullptr;

Warrior::Warrior() 
    : m_x(0), m_y(0), m_speed(0), m_scale(1.0f),
      m_animSpeed(0), m_animTimer(0), m_currentFrame(0),
      m_state(State::RUNNING), m_runTexture(nullptr), m_deathTexture(nullptr) {
}

Warrior::~Warrior() {
    // Textures are managed by pool
}

void Warrior::Initialize(float x, float y, float speed, float animSpeed, float scale) {
    m_x = x;
    m_y = y;
    m_speed = speed;
    m_animSpeed = animSpeed;
    m_scale = scale;
    m_animTimer = 0.0f;
    m_currentFrame = 0;
    m_state = State::RUNNING;

    // Load textures
    if (!m_runTexture) {
        m_runTexture = Texture::Pool->GetResource();
        m_runTexture->Load("Assets/Textures/warrior_run.tga");
    }

    if (!m_deathTexture) {
        m_deathTexture = Texture::Pool->GetResource();
        m_deathTexture->Load("Assets/Textures/warrior_death.tga");
    }
}

void Warrior::Update(float deltaTime) {
    if (m_state == State::DEAD) {
        return;
    }

    // Move warrior
    if (m_state == State::RUNNING) {
        m_x += m_speed * deltaTime;
    }

    // Update animation
    m_animTimer += deltaTime * m_animSpeed;

    if (m_animTimer >= 1.0f) {
        m_animTimer -= 1.0f;

        if (m_state == State::RUNNING) {
            m_currentFrame = (m_currentFrame + 1) % RUN_FRAMES;
        } else if (m_state == State::DYING) {
            m_currentFrame++;
            if (m_currentFrame >= DEATH_FRAMES) {
                m_state = State::DEAD;
            }
        }
    }
}

void Warrior::Render(Renderer* renderer) {
    if (m_state == State::DEAD) {
        return;
    }

    Texture* currentTexture = (m_state == State::RUNNING) ? m_runTexture : m_deathTexture;
    int totalFrames = (m_state == State::RUNNING) ? RUN_FRAMES : DEATH_FRAMES;

    if (currentTexture) {
        renderer->RenderAnimatedTexture(currentTexture, m_currentFrame, totalFrames,
                                        m_x, m_y, m_scale);
    }
}

void Warrior::StartDeathAnimation() {
    if (m_state == State::RUNNING) {
        m_state = State::DYING;
        m_currentFrame = 0;
        m_animTimer = 0.0f;
    }
}

void Warrior::Serialize(std::ostream& stream) {
    stream.write(reinterpret_cast<const char*>(&m_x), sizeof(float));
    stream.write(reinterpret_cast<const char*>(&m_y), sizeof(float));
    stream.write(reinterpret_cast<const char*>(&m_speed), sizeof(float));
    stream.write(reinterpret_cast<const char*>(&m_scale), sizeof(float));
    stream.write(reinterpret_cast<const char*>(&m_animSpeed), sizeof(float));
    stream.write(reinterpret_cast<const char*>(&m_animTimer), sizeof(float));
    stream.write(reinterpret_cast<const char*>(&m_currentFrame), sizeof(int));

    int stateInt = static_cast<int>(m_state);
    stream.write(reinterpret_cast<const char*>(&stateInt), sizeof(int));
}

void Warrior::Deserialize(std::istream& stream) {
    stream.read(reinterpret_cast<char*>(&m_x), sizeof(float));
    stream.read(reinterpret_cast<char*>(&m_y), sizeof(float));
    stream.read(reinterpret_cast<char*>(&m_speed), sizeof(float));
    stream.read(reinterpret_cast<char*>(&m_scale), sizeof(float));
    stream.read(reinterpret_cast<char*>(&m_animSpeed), sizeof(float));
    stream.read(reinterpret_cast<char*>(&m_animTimer), sizeof(float));
    stream.read(reinterpret_cast<char*>(&m_currentFrame), sizeof(int));

    int stateInt;
    stream.read(reinterpret_cast<char*>(&stateInt), sizeof(int));
    m_state = static_cast<State>(stateInt);

    // Reload textures
    if (!m_runTexture) {
        m_runTexture = Texture::Pool->GetResource();
        m_runTexture->Load("Assets/Textures/warrior_run.tga");
    }

    if (!m_deathTexture) {
        m_deathTexture = Texture::Pool->GetResource();
        m_deathTexture->Load("Assets/Textures/warrior_death.tga");
    }
}
