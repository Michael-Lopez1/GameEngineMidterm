#include "../Include/Renderer.h"

Renderer::Renderer() : m_window(nullptr), m_renderer(nullptr) {
}

Renderer::~Renderer() {
    Shutdown();
}

bool Renderer::Initialize(const char* title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return false;
    }

    m_window = SDL_CreateWindow(title, width, height, 0);
    if (!m_window) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        return false;
    }

    m_renderer = SDL_CreateRenderer(m_window, nullptr);
    if (!m_renderer) {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);

    return true;
}

void Renderer::Shutdown() {
    // Clean up texture cache
    for (auto& pair : m_textureCache) {
        SDL_DestroyTexture(pair.second);
    }
    m_textureCache.clear();

    if (m_renderer) {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
    }

    if (m_window) {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }

    SDL_Quit();
}

void Renderer::Clear() {
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);
}

void Renderer::ClearWithColor(SDL_Color color) {
    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(m_renderer);
}

void Renderer::Present() {
    SDL_RenderPresent(m_renderer);
}

void Renderer::CreateSDLTexture(Texture* texture) {
    if (!texture || !texture->GetImageInfo()) {
        return;
    }

    ImageInfo* info = texture->GetImageInfo();
    
    Uint32 format = (info->BitsPerPixel == 32) ? SDL_PIXELFORMAT_RGBA32 : SDL_PIXELFORMAT_RGB24;
    
    SDL_Texture* sdlTexture = SDL_CreateTexture(
        m_renderer,
        format,
        SDL_TEXTUREACCESS_STATIC,
        info->Width,
        info->Height
    );

    if (sdlTexture) {
        SDL_SetTextureBlendMode(sdlTexture, SDL_BLENDMODE_BLEND);
        SDL_UpdateTexture(sdlTexture, nullptr, info->Data, 
                         info->Width * (info->BitsPerPixel / 8));
        m_textureCache[texture] = sdlTexture;
    }
}

SDL_Texture* Renderer::GetSDLTexture(Texture* texture) {
    if (!texture) return nullptr;

    auto it = m_textureCache.find(texture);
    if (it != m_textureCache.end()) {
        return it->second;
    }

    CreateSDLTexture(texture);
    return m_textureCache[texture];
}

void Renderer::RenderTexture(Texture* texture, float x, float y, float scale) {
    SDL_Texture* sdlTexture = GetSDLTexture(texture);
    if (!sdlTexture) return;

    ImageInfo* info = texture->GetImageInfo();
    
    SDL_FRect destRect = {
        x,
        y,
        info->Width * scale,
        info->Height * scale
    };

    SDL_RenderTexture(m_renderer, sdlTexture, nullptr, &destRect);
}

void Renderer::RenderAnimatedTexture(Texture* texture, int frame, int totalFrames,
                                     float x, float y, float scale) {
    SDL_Texture* sdlTexture = GetSDLTexture(texture);
    if (!sdlTexture) return;

    ImageInfo* info = texture->GetImageInfo();
    int frameWidth = info->Width / totalFrames;

    SDL_Rect srcRect = {
        frame * frameWidth,
        0,
        frameWidth,
        info->Height
    };

    SDL_FRect destRect = {
        x,
        y,
        frameWidth * scale,
        info->Height * scale
    };

    SDL_RenderTexture(m_renderer, sdlTexture, &srcRect, &destRect);
}

void Renderer::RenderText(const std::string& text, int x, int y, SDL_Color color) {
    // Simple debug text rendering using SDL's built-in capabilities
    // For a full implementation, you would use SDL_ttf
    // For now, we'll just render colored rectangles to indicate text position
    
    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
    
    // Simple placeholder - render a small rectangle for each character
    int charWidth = 8;
    int charHeight = 12;
    
    for (size_t i = 0; i < text.length(); ++i) {
        SDL_FRect rect = {
            (float)(x + i * charWidth),
            (float)y,
            (float)charWidth - 1,
            (float)charHeight
        };
        SDL_RenderRect(m_renderer, &rect);
    }
}
