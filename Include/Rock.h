#pragma once

#include "StandardIncludes.h"
#include "Resource.h"
#include "Texture.h"
#include "ObjectPool.h"

class Renderer;

class Rock : public Resource {
public:
    Rock();
    virtual ~Rock();

    void Initialize(float x, float y, float speed, float animSpeed, float scale);
    void Update(float deltaTime);
    void Render(Renderer* renderer);

    bool IsActive() const { return m_active; }
    void SetActive(bool active) { m_active = active; }
    bool IsOffScreen() const { return m_y > 1080.0f; }

    float GetX() const { return m_x; }
    float GetY() const { return m_y; }
    float GetWidth() const { return 64.0f * m_scale; }
    float GetHeight() const { return 64.0f * m_scale; }

    virtual void Serialize(std::ostream& stream) override;
    virtual void Deserialize(std::istream& stream) override;

    static ObjectPool<Rock>* Pool;

private:
    static const int FRAMES = 4;

    float m_x, m_y;
    float m_speed;
    float m_scale;
    float m_animSpeed;
    float m_animTimer;
    int m_currentFrame;
    bool m_active;

    Texture* m_texture;
};
