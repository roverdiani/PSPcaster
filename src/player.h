#ifndef PLAYER_H
#define PLAYER_H

#include <cstdint>
#include <memory>
#include "defines.h"
#include "display.h"
#include "map.h"
#include "vec2.h"

enum WalkDirection
{
    WALK_NONE,
    WALK_FORWARD,
    WALK_BACKWARD
};

enum TurnDirection
{
    TURN_NONE,
    TURN_LEFT,
    TURN_RIGHT
};

class Player
{
public:
    Player(float x, float y);

    void Move(float deltaTime, const std::shared_ptr<Map> &map);
    void Render(const std::shared_ptr<Display> &display) const;

    vec2 GetPosition();
    float GetRotationAngle();

    void SetWalkDirection(WalkDirection direction);
    void SetTurnDirection(TurnDirection direction);

private:
    vec2 m_position;
    vec2 m_size;

    int32_t m_turnDirection = 0;
    int32_t m_walkDirection = 0;

    float m_rotationAngle = M_PI / 2.0f;
    float m_walkSpeed = 100.0f;
    float m_turnSpeed = 45.0f * M_PI / 180.0f;
};

#endif