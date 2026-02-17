#pragma once

#include "StandardIncludes.h"
#include "Singleton.h"
#include "Level.h"
#include "Renderer.h"

class GameController : public Singleton<GameController> {
public:
    GameController();
    virtual ~GameController();

    void RunGame();

private:
    void Initialize();
    void Update(float deltaTime);
    void Render();
    void Shutdown();

    void CalculateFPS(float deltaTime);
    void RenderUI();
    void HandleLevelTransition();

    Level* m_currentLevel;
    Renderer* m_renderer;
    SDL_Event m_event;
    bool m_running;

    // Timing
    Uint64 m_lastTime;
    float m_deltaTime;
    float m_fps;
    int m_frameCount;
    float m_fpsTimer;
};
