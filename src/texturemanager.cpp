#include "texturemanager.h"

static const char *textureFileNames[NUM_TEXTURES] = {
        "assets/redbrick.png",
        "assets/purplestone.png",
        "assets/mossystone.png",
        "assets/graystone.png",
        "assets/colorstone.png",
        "assets/bluestone.png",
        "assets/wood.png"
};

TextureManager::TextureManager()
{
    for (size_t i = 0; i < NUM_TEXTURES; i++)
        m_textures[i] = std::make_shared<Texture>(textureFileNames[i]);
}

std::shared_ptr<Texture> TextureManager::GetTexture(int32_t index)
{
    return m_textures[index];
}