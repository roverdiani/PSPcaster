#ifndef DISPLAY_H
#define DISPLAY_H

#include <cstdint>
#include <SDL2/SDL.h>

class Display
{
public:
    Display(uint32_t width, uint32_t height);
    ~Display();

    void RenderFrame();

    void DrawPixel(int32_t x, int32_t y, uint32_t color);
    void DrawRect(int32_t x, int32_t y, int32_t width, int32_t height, uint32_t color);
    void DrawLine(int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t color);

private:
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;

    uint32_t m_windowWidth;
    uint32_t m_windowHeight;

    uint32_t *m_colorBuffer;
    SDL_Texture *m_colorBufferTexture;
};

#endif