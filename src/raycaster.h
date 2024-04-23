#ifndef RAYCASTER_H
#define RAYCASTER_H

#include <array>
#include <memory>
#include "defines.h"
#include "display.h"
#include "player.h"
#include "ray.h"
#include "map.h"
#include "texturemanager.h"

class Raycaster
{
public:
    void CastRays(const std::shared_ptr<Player> &player, const std::shared_ptr<Map> &map);
    void RenderRays(const std::shared_ptr<Display> &display, const std::shared_ptr<Player> &player);
    void RenderWalls(const std::shared_ptr<Display> &display, const std::shared_ptr<Player> &player, const std::shared_ptr<TextureManager> &textureManager);

private:
    std::array<Ray, SCREEN_WIDTH> m_rays;
};

#endif