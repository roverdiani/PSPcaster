#include "raycaster.h"
#include <cmath>
#include "texture.h"

void ChangeColorIntensity(uint32_t &color, float factor)
{
    uint32_t a = (color & 0xFF000000);
    uint32_t r = (color & 0x00FF0000) * factor;
    uint32_t g = (color & 0x0000FF00) * factor;
    uint32_t b = (color & 0x000000FF) * factor;

    color = a | (r & 0x00FF0000) | (g & 0x0000FF00) | (b & 0x000000FF);
}

void Raycaster::CastRays(const std::shared_ptr<Player> &player, const std::shared_ptr<Map> &map)
{
    int32_t numRays = m_rays.size();
    for (int32_t col = 0; col < numRays; col++)
    {
        float rayAngle = player->GetRotationAngle() + atanf((col - numRays / 2) / DIST_PROJ_PLANE);
        m_rays[col].Cast(rayAngle, player, map);
    }
}

void Raycaster::RenderRays(const std::shared_ptr<Display> &display, const std::shared_ptr<Player> &player)
{
    vec2 playerPosition = player->GetPosition();
    for (auto & ray : m_rays)
    {
        vec2 rayHitPosition = ray.GetHitPosition();

        display->DrawLine(
                (int32_t) (playerPosition.x * MINIMAP_SCALE_FACTOR),
                (int32_t) (playerPosition.y * MINIMAP_SCALE_FACTOR),
                (int32_t) (rayHitPosition.x * MINIMAP_SCALE_FACTOR),
                (int32_t) (rayHitPosition.y * MINIMAP_SCALE_FACTOR),
                0xFF0000FF
        );
    }
}

void Raycaster::RenderWalls(const std::shared_ptr<Display> &display, const std::shared_ptr<Player> &player, const std::shared_ptr<TextureManager> &textureManager)
{
    for (int x = 0; x < m_rays.size(); x++)
    {
        Ray &ray = m_rays[x];

        float perpendicularDistance = ray.GetHitDistance() * cosf(ray.GetAngle() - player->GetRotationAngle());
        int32_t wallStripHeight = (int32_t) ((TILE_SIZE / perpendicularDistance) * DIST_PROJ_PLANE);

        int32_t wallTopPixel = (SCREEN_HEIGHT / 2) - (wallStripHeight / 2);
        if (wallTopPixel < 0)
            wallTopPixel = 0;

        int32_t wallBottomPixel = (SCREEN_HEIGHT / 2) + (wallStripHeight / 2);
        if (wallBottomPixel > SCREEN_HEIGHT)
            wallBottomPixel = SCREEN_HEIGHT;

        // Ceiling rendering
        for (int32_t  y = 0; y < wallTopPixel; y++)
            display->DrawPixel(x, y, 0xFF444444);

        // Wall rendering
        bool rayWasHitVertical = ray.GetWasHitVertical();
        int32_t textureOffsetX = (int32_t) (rayWasHitVertical ? ray.GetHitPosition().y : ray.GetHitPosition().x) % TILE_SIZE;
        int32_t textureIndex = ray.GetWallHitContent() - 1;
        std::shared_ptr<Texture> texture = textureManager->GetTexture(textureIndex);
        uint32_t textureWidth = texture->GetWidth();
        uint32_t textureHeight = texture->GetHeight();

        for (int y = wallTopPixel; y < wallBottomPixel; y++)
        {
            int32_t distanceFromTop = y + (wallStripHeight / 2) - (SCREEN_HEIGHT / 2);
            int32_t textureOffsetY = distanceFromTop * ((float) textureHeight / wallStripHeight);

            uint32_t texelColor = texture->GetBuffer()[(textureWidth * textureOffsetY) + textureOffsetX];

            if (rayWasHitVertical)
                ChangeColorIntensity(texelColor, 0.7f);

            display->DrawPixel(x, y, texelColor);
        }

        // Floor rendering
        for (int y = wallBottomPixel; y < SCREEN_HEIGHT; y++)
            display->DrawPixel(x, y, 0xFF888888);
    }
}
