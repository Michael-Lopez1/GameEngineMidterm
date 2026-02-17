#pragma once

#include "StandardIncludes.h"
#include "Singleton.h"
#include "Texture.h"
#include <map>

class Renderer : public Singleton<Renderer> {
public:
    Renderer();
    virtual ~Renderer();

    bool Initialize(const char* title, int width, int height);
    void Shutdown();

    void Clear();
    void ClearWithColor(SDL_Color color);
    void Present();

    void RenderTexture(Texture* texture, float x, float y, float scale = 1.0f);
    void RenderAnimatedTexture(Texture* texture, int frame, int totalFrames,
                               float x, float y, float scale);
    void RenderText(const std::string& text, int x, int y, SDL_Color color);

    SDL_Renderer* GetSDLRenderer() { return m_renderer; }
    SDL_Texture* GetSDLTexture(Texture* texture);

private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    std::map<Texture*, SDL_Texture*> m_textureCache;

    void CreateSDLTexture(Texture* texture);
};
