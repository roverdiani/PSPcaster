#include "ray.h"
#include <cmath>
#include "defines.h"

float Ray::NormalizeAngle(float angle)
{
    // Get the value exceeding a full revolution
    float remainder = remainderf(angle, M_PI * 2);

    // If the value is negative, subtract it from 360 degrees.
    if (remainder < 0)
        return (float) (M_PI * 2) + remainder;

    return remainder;
}

inline float DistanceBetweenPoints(vec2 p1, vec2 p2)
{
    return sqrtf((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
}

bool Ray::IsFacingDown() const
{
    // The ray is facing down if the angle is greater than 0 and less than 180 degrees
    return m_angle > 0 && m_angle < M_PI;
}

bool Ray::IsFacingRight() const
{
    // The ray is facing right if the angle is less than 90 or greater than 270 degrees
    return m_angle < 0.5 * M_PI || m_angle > 1.5 * M_PI;
}

void Ray::Cast(float angle, const std::shared_ptr<Player> &player, const std::shared_ptr<Map> &map)
{
    m_angle = NormalizeAngle(angle);

    vec2 playerPosition = player->GetPosition();

    vec2 intercept;
    vec2 step;

    // Horizontal Ray-Grid Intersection
    bool foundHorizontalWallHit = false;
    vec2 horizontalWallHit;
    int32_t horizontalWallContent;

    intercept.y = floorf(playerPosition.y / TILE_SIZE) * TILE_SIZE;
    intercept.y += IsFacingDown() ? TILE_SIZE : 0;

    intercept.x = playerPosition.x + (intercept.y - playerPosition.y) / tanf(m_angle);

    step.y = TILE_SIZE;
    if (!IsFacingDown())
        step.y *= -1;

    step.x = TILE_SIZE / tanf(m_angle);
    if (!IsFacingRight() && step.x > 0)
        step.x *= -1;
    if (IsFacingRight() && step.x < 0)
        step.x *= -1;

    vec2 nextHorizontalTouch = intercept;

    while (map->IsInside(nextHorizontalTouch))
    {
        vec2 posToCheck = vec2(nextHorizontalTouch.x, nextHorizontalTouch.y + (!IsFacingDown() ? -1.0f : 0.0f));
        if (map->HasWallAt(posToCheck))
        {
            horizontalWallHit = nextHorizontalTouch;
            horizontalWallContent = map->GetAt((int)floorf(posToCheck.y / TILE_SIZE), (int)floorf(posToCheck.x / TILE_SIZE));
            foundHorizontalWallHit = true;
            break;
        }

        nextHorizontalTouch += step;
    }

    // Vertical Ray-Grid Intersection
    bool foundVerticalWallHit = false;
    vec2 verticalWallHit;
    int32_t verticalWallHitContent;

    intercept.x = floorf(playerPosition.x / TILE_SIZE) * TILE_SIZE;
    intercept.x += IsFacingRight() ? TILE_SIZE : 0;

    intercept.y = playerPosition.y + (intercept.x - playerPosition.x) * tanf(m_angle);

    step.x = TILE_SIZE;
    if (!IsFacingRight())
        step.x *= -1;

    step.y = TILE_SIZE * tanf(m_angle);
    if (!IsFacingDown() && step.y > 0)
        step.y *= -1;
    if (IsFacingDown() && step.y < 0)
        step.y *= -1;

    vec2 nextVerticalTouch = intercept;

    while (map->IsInside(nextVerticalTouch))
    {
        vec2 posToCheck = vec2(nextVerticalTouch.x + (!IsFacingRight() ? -1.0f : 0.0f), nextVerticalTouch.y);
        if (map->HasWallAt(posToCheck))
        {
            verticalWallHit = nextVerticalTouch;

            verticalWallHitContent = map->GetAt((int)floorf(posToCheck.y / TILE_SIZE), (int)floorf(posToCheck.x / TILE_SIZE));
            foundVerticalWallHit = true;
            break;
        }

        nextVerticalTouch += step;
    }

    float horizontalHitDistance = foundHorizontalWallHit ? DistanceBetweenPoints(playerPosition, horizontalWallHit) : FLT_MAX;
    float verticalHitDistance = foundVerticalWallHit ? DistanceBetweenPoints(playerPosition, verticalWallHit) : FLT_MAX;

    if (verticalHitDistance < horizontalHitDistance)
    {
        m_hitDistance = verticalHitDistance;
        m_wallHitPosition = verticalWallHit;
        m_wallHitContent = verticalWallHitContent;
        m_wasHitVertical = true;
    }
    else
    {
        m_hitDistance = horizontalHitDistance;
        m_wallHitPosition = horizontalWallHit;
        m_wallHitContent = horizontalWallContent;
        m_wasHitVertical = false;
    }
}

float Ray::GetAngle()
{
    return m_angle;
}

float Ray::GetHitDistance()
{
    return m_hitDistance;
}

vec2 Ray::GetHitPosition()
{
    return m_wallHitPosition;
}

bool Ray::GetWasHitVertical()
{
    return m_wasHitVertical;
}

int32_t Ray::GetWallHitContent()
{
    return m_wallHitContent;
}