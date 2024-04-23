#include "texture.h"

Texture::Texture(const std::string &filename)
{
    upng_t *m_upngTexture = upng_new_from_file(filename.c_str());
    upng_decode(m_upngTexture);

    m_width = upng_get_width(m_upngTexture);
    m_height = upng_get_height(m_upngTexture);
    m_buffer = (uint32_t*) upng_get_buffer(m_upngTexture);
}

Texture::~Texture()
{
    upng_free(m_upngTexture);
}

uint32_t Texture::GetWidth()
{
    return m_width;
}

uint32_t Texture::GetHeight()
{
    return m_height;
}

uint32_t* Texture::GetBuffer()
{
    return m_buffer;
}