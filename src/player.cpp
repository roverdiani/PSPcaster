#include "player.h"
#include "defines.h"

Player::Player(float x, float y)
{
    m_position = vec2(x, y);
    m_size = vec2(1.0f, 1.0f);
}

void Player::Move(float deltaTime, const std::shared_ptr<Map> &map)
{
    m_rotationAngle += m_turnDirection * m_turnSpeed * deltaTime;

    float moveStep = m_walkDirection * m_walkSpeed * deltaTime;
    vec2 newPlayerPos(
        m_position.x + cosf(m_rotationAngle) * moveStep,
        m_position.y + sinf(m_rotationAngle) * moveStep
    );

    if (map->HasWallAt(newPlayerPos))
        return;

    m_position = newPlayerPos;
}

void Player::Render(const std::shared_ptr<Display> &display) const
{
    display->DrawRect(
        (int32_t) (m_position.x * MINIMAP_SCALE_FACTOR),
        (int32_t) (m_position.y * MINIMAP_SCALE_FACTOR),
        (int32_t) (m_size.x * MINIMAP_SCALE_FACTOR),
        (int32_t) (m_size.y * MINIMAP_SCALE_FACTOR),
        0xFF0000FF
    );
}

vec2 Player::GetPosition()
{
    return m_position;
}

float Player::GetRotationAngle()
{
    return m_rotationAngle;
}

void Player::SetWalkDirection(WalkDirection direction)
{
    if (direction == WALK_FORWARD)
        m_walkDirection = +1;
    else if (direction == WALK_BACKWARD)
        m_walkDirection = -1;
    else
        m_walkDirection = 0;
}

void Player::SetTurnDirection(TurnDirection direction)
{
    if (direction == TURN_RIGHT)
        m_turnDirection = +1;
    else if (direction == TURN_LEFT)
        m_turnDirection = -1;
    else
        m_turnDirection = 0;
}