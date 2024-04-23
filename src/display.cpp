#include "display.h"

Display::Display(uint32_t width, uint32_t height)
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_TIMER);

    m_windowWidth = width;
    m_windowHeight = height;

    m_window = SDL_CreateWindow(
        "raycaster",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        (int32_t) m_windowWidth,
        (int32_t) m_windowHeight,
        0
    );

    m_renderer = SDL_CreateRenderer(
        m_window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);

    m_colorBuffer = (uint32_t*) malloc(sizeof(uint32_t) * m_windowWidth * m_windowHeight);
    m_colorBufferTexture = SDL_CreateTexture(
        m_renderer,
        SDL_PIXELFORMAT_RGBA32,
        SDL_TEXTUREACCESS_STREAMING,
        m_windowWidth,
        m_windowHeight
    );
}

Display::~Display()
{
    free(m_colorBuffer);
    SDL_DestroyTexture(m_colorBufferTexture);
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Display::RenderFrame()
{
    SDL_UpdateTexture(
        m_colorBufferTexture,
        nullptr,
        m_colorBuffer,
        (int32_t) (m_windowWidth * sizeof(uint32_t))
    );
    SDL_RenderCopy(m_renderer, m_colorBufferTexture, nullptr, nullptr);
    SDL_RenderPresent(m_renderer);
}

void Display::DrawPixel(int32_t x, int32_t y, uint32_t color)
{
    m_colorBuffer[(m_windowWidth * y) + x] = color;
}

void Display::DrawRect(int32_t x, int32_t y, int32_t width, int32_t height, uint32_t color)
{
    for (int32_t i = x; i <= x + width; i++)
        for (int32_t j = y; j <= y + height; j++)
            DrawPixel(i, j, color);
}

void Display::DrawLine(int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t color)
{
    int32_t deltaX = x1 - x0;
    int32_t deltaY = y1 - y0;

    int32_t longestSideLength = (abs(deltaX) >= abs(deltaY)) ? abs(deltaX) : abs(deltaY);

    float xIncrement = deltaX / (float) longestSideLength;
    float yIncrement = deltaY / (float) longestSideLength;

    float currentX = x0;
    float currentY = y0;

    for (int32_t i = 0; i < longestSideLength; i++)
    {
        DrawPixel(round(currentX), round(currentY), color);
        currentX += xIncrement;
        currentY += yIncrement;
    }
}