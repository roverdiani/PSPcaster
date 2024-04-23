#ifndef RAY_H
#define RAY_H

#include <cstdint>
#include <memory>
#include "player.h"
#include "map.h"
#include "vec2.h"

class Ray
{
public:
    void Cast(float angle, const std::shared_ptr<Player> &player, const std::shared_ptr<Map> &map);

    float GetAngle();
    float GetHitDistance();
    vec2 GetHitPosition();
    bool GetWasHitVertical();
    int32_t GetWallHitContent();

private:
    bool IsFacingDown() const;
    bool IsFacingRight() const;

    static float NormalizeAngle(float angle);

    float m_angle;
    float m_hitDistance;
    vec2 m_wallHitPosition;
    bool m_wasHitVertical;
    int32_t m_wallHitContent;
};

#endif