#include "../Include/Rock.h"
#include "../Include/Renderer.h"

ObjectPool<Rock>* Rock::Pool = nullptr;

Rock::Rock()
    : m_x(0), m_y(0), m_speed(0), m_scale(1.0f),
      m_animSpeed(0), m_animTimer(0), m_currentFrame(0),
      m_active(true), m_texture(nullptr) {
}

Rock::~Rock() {
    // Texture is managed by pool
}

void Rock::Initialize(float x, float y, float speed, float animSpeed, float scale) {
    m_x = x;
    m_y = y;
    m_speed = speed;
    m_animSpeed = animSpeed;
    m_scale = scale;
    m_animTimer = 0.0f;
    m_currentFrame = 0;
    m_active = true;

    // Load texture
    if (!m_texture) {
        m_texture = Texture::Pool->GetResource();
        m_texture->Load("Assets/Textures/rock.tga");
    }
}

void Rock::Update(float deltaTime) {
    if (!m_active) {
        return;
    }

    // Move rock downward
    m_y += m_speed * deltaTime;

    // Update animation
    m_animTimer += deltaTime * m_animSpeed;

    if (m_animTimer >= 1.0f) {
        m_animTimer -= 1.0f;
        m_currentFrame = (m_currentFrame + 1) % FRAMES;
    }
}

void Rock::Render(Renderer* renderer) {
    if (!m_active || !m_texture) {
        return;
    }

    renderer->RenderAnimatedTexture(m_texture, m_currentFrame, FRAMES,
                                    m_x, m_y, m_scale);
}

void Rock::Serialize(std::ostream& stream) {
    stream.write(reinterpret_cast<const char*>(&m_x), sizeof(float));
    stream.write(reinterpret_cast<const char*>(&m_y), sizeof(float));
    stream.write(reinterpret_cast<const char*>(&m_speed), sizeof(float));
    stream.write(reinterpret_cast<const char*>(&m_scale), sizeof(float));
    stream.write(reinterpret_cast<const char*>(&m_animSpeed), sizeof(float));
    stream.write(reinterpret_cast<const char*>(&m_animTimer), sizeof(float));
    stream.write(reinterpret_cast<const char*>(&m_currentFrame), sizeof(int));
    stream.write(reinterpret_cast<const char*>(&m_active), sizeof(bool));
}

void Rock::Deserialize(std::istream& stream) {
    stream.read(reinterpret_cast<char*>(&m_x), sizeof(float));
    stream.read(reinterpret_cast<char*>(&m_y), sizeof(float));
    stream.read(reinterpret_cast<char*>(&m_speed), sizeof(float));
    stream.read(reinterpret_cast<char*>(&m_scale), sizeof(float));
    stream.read(reinterpret_cast<char*>(&m_animSpeed), sizeof(float));
    stream.read(reinterpret_cast<char*>(&m_animTimer), sizeof(float));
    stream.read(reinterpret_cast<char*>(&m_currentFrame), sizeof(int));
    stream.read(reinterpret_cast<char*>(&m_active), sizeof(bool));

    // Reload texture
    if (!m_texture) {
        m_texture = Texture::Pool->GetResource();
        m_texture->Load("Assets/Textures/rock.tga");
    }
}
