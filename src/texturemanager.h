#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <array>
#include <memory>
#include "texture.h"

#define NUM_TEXTURES 7

class TextureManager
{
public:
    TextureManager();

    std::shared_ptr<Texture> GetTexture(int32_t index);

private:
    std::array<std::shared_ptr<Texture>, NUM_TEXTURES> m_textures;
};

#endif