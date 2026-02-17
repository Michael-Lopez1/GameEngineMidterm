#pragma once

#include "StandardIncludes.h"
#include "Resource.h"
#include "Texture.h"
#include "ObjectPool.h"

class Renderer;

class Warrior : public Resource {
public:
    enum class State { RUNNING, DYING, DEAD };

    Warrior();
    virtual ~Warrior();

    void Initialize(float x, float y, float speed, float animSpeed, float scale);
    void Update(float deltaTime);
    void Render(Renderer* renderer);

    void StartDeathAnimation();
    bool IsAlive() const { return m_state == State::RUNNING; }
    bool IsDying() const { return m_state == State::DYING; }
    bool IsDead() const { return m_state == State::DEAD; }
    bool IsOffScreen() const { return m_x > 1920.0f; }

    float GetX() const { return m_x; }
    float GetY() const { return m_y; }
    float GetWidth() const { return 64.0f * m_scale; }
    float GetHeight() const { return 64.0f * m_scale; }

    virtual void Serialize(std::ostream& stream) override;
    virtual void Deserialize(std::istream& stream) override;

    static ObjectPool<Warrior>* Pool;

private:
    static const int RUN_FRAMES = 6;
    static const int DEATH_FRAMES = 8;

    float m_x, m_y;
    float m_speed;
    float m_scale;
    float m_animSpeed;
    float m_animTimer;
    int m_currentFrame;
    State m_state;

    Texture* m_runTexture;
    Texture* m_deathTexture;
};
