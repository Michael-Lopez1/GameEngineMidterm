#include "../Include/GameController.h"
#include "../Include/Level1.h"
#include "../Include/Level2.h"
#include "../Include/AssetController.h"
#include <sstream>
#include <iomanip>

GameController::GameController()
    : m_currentLevel(nullptr), m_renderer(nullptr), m_running(false),
      m_lastTime(0), m_deltaTime(0), m_fps(0), m_frameCount(0), m_fpsTimer(0) {
}

GameController::~GameController() {
    Shutdown();
}

void GameController::Initialize() {
    // Initialize object pools
    Warrior::Pool = new ObjectPool<Warrior>(20);
    Rock::Pool = new ObjectPool<Rock>(20);
    Texture::Pool = new ObjectPool<Texture>(10);

    // Initialize renderer
    m_renderer = Renderer::GetInstance();
    if (!m_renderer->Initialize("SDLLevels - Game Engine Midterm", 1920, 1080)) {
        std::cerr << "Failed to initialize renderer!" << std::endl;
        return;
    }

    // Initialize asset controller
    AssetController::GetInstance()->Initialize(10 * 1024 * 1024); // 10 MB

    // Create Level 1
    m_currentLevel = new Level1();
    m_currentLevel->Initialize();

    m_running = true;
    m_lastTime = SDL_GetPerformanceCounter();
}

void GameController::RunGame() {
    Initialize();

    while (m_running) {
        // Calculate delta time
        Uint64 currentTime = SDL_GetPerformanceCounter();
        m_deltaTime = (float)((currentTime - m_lastTime) / (double)SDL_GetPerformanceFrequency());
        m_lastTime = currentTime;

        // Cap delta time to prevent huge jumps
        if (m_deltaTime > 0.1f) {
            m_deltaTime = 0.1f;
        }

        // Handle events
        while (SDL_PollEvent(&m_event)) {
            if (m_event.type == SDL_EVENT_QUIT) {
                m_running = false;
            }
            if (m_event.type == SDL_EVENT_KEY_DOWN) {
                if (m_event.key.key == SDLK_ESCAPE) {
                    m_running = false;
                }
            }
        }

        Update(m_deltaTime);
        Render();

        // Check quit conditions
        if (m_currentLevel && m_currentLevel->ShouldQuit()) {
            m_running = false;
        }
    }

    Shutdown();
}

void GameController::Update(float deltaTime) {
    CalculateFPS(deltaTime);

    if (m_currentLevel) {
        m_currentLevel->Update(deltaTime);
        HandleLevelTransition();
    }
}

void GameController::Render() {
    if (m_currentLevel) {
        m_renderer->ClearWithColor(m_currentLevel->GetBackgroundColor());
        m_currentLevel->Render(m_renderer);
        RenderUI();
        m_renderer->Present();
    }
}

void GameController::Shutdown() {
    if (m_currentLevel) {
        delete m_currentLevel;
        m_currentLevel = nullptr;
    }

    AssetController::DestroyInstance();
    Renderer::DestroyInstance();

    // Clean up object pools
    if (Warrior::Pool) {
        delete Warrior::Pool;
        Warrior::Pool = nullptr;
    }
    if (Rock::Pool) {
        delete Rock::Pool;
        Rock::Pool = nullptr;
    }
    if (Texture::Pool) {
        delete Texture::Pool;
        Texture::Pool = nullptr;
    }
}

void GameController::CalculateFPS(float deltaTime) {
    m_fpsTimer += deltaTime;
    m_frameCount++;

    if (m_fpsTimer >= 1.0f) {
        m_fps = m_frameCount / m_fpsTimer;
        m_frameCount = 0;
        m_fpsTimer = 0.0f;
    }
}

void GameController::RenderUI() {
    if (!m_currentLevel) return;

    SDL_Color blueColor = {0, 0, 255, 255};

    // FPS Label
    std::ostringstream fpsStream;
    fpsStream << "FPS: " << std::fixed << std::setprecision(1) << m_fps;
    m_renderer->RenderText(fpsStream.str(), 10, 10, blueColor);

    // Time Label
    std::ostringstream timeStream;
    timeStream << "Time: " << std::fixed << std::setprecision(2) << m_currentLevel->GetGameTime() << "s";
    m_renderer->RenderText(timeStream.str(), 200, 10, blueColor);

    // Status Label
    std::string status = m_currentLevel->IsAutoSaved() ? "Saved" : "Not Saved";
    std::ostringstream statusStream;
    statusStream << "Status: " << status;
    m_renderer->RenderText(statusStream.str(), 400, 10, blueColor);
}

void GameController::HandleLevelTransition() {
    if (m_currentLevel && m_currentLevel->ShouldTransition()) {
        if (m_currentLevel->GetLevelNumber() == 1) {
            // Transition to Level 2
            std::vector<Warrior*> warriors = m_currentLevel->GetWarriors();
            
            delete m_currentLevel;
            
            Level2* level2 = new Level2(warriors);
            level2->Initialize();
            m_currentLevel = level2;

            std::cout << "Transitioned to Level 2" << std::endl;
        }
    }
}
