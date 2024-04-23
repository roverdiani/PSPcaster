#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include "upng.h"

class Texture
{
public:
    Texture(const std::string &filename);
    ~Texture();

    uint32_t GetWidth();
    uint32_t GetHeight();
    uint32_t *GetBuffer();

private:
    uint32_t m_width;
    uint32_t m_height;
    uint32_t *m_buffer;
    upng_t *m_upngTexture;
};

#endif