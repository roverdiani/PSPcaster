#include "map.h"
#include "defines.h"

int32_t Map::m_mapData[MAP_NUM_ROWS][MAP_NUM_COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 2, 2, 0, 3, 0, 4, 0, 5, 0, 6, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 5},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 5},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 5},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 5, 5, 5, 5, 5}
};

void Map::Render(const std::shared_ptr<Display> &display)
{
    for (size_t i = 0; i < MAP_NUM_ROWS; i++)
    {
        for (size_t j = 0; j < MAP_NUM_COLS; j++)
        {
            int32_t tileX = j * TILE_SIZE;
            int32_t tileY = i * TILE_SIZE;
            uint32_t tileColor = m_mapData[i][j] != 0 ? 0x99FFFFFF : 0x00000000;
            display->DrawRect(
                tileX * MINIMAP_SCALE_FACTOR,
                tileY * MINIMAP_SCALE_FACTOR,
                TILE_SIZE * MINIMAP_SCALE_FACTOR,
                TILE_SIZE * MINIMAP_SCALE_FACTOR,
                tileColor
            );
        }
    }
}

bool Map::HasWallAt(vec2 pos)
{
    if (!IsInside(pos))
        return true;
    
    int32_t mapGridIndexX = (int32_t) floorf(pos.x / TILE_SIZE);
    int32_t mapGridIndexY = (int32_t) floorf(pos.y / TILE_SIZE);

    return m_mapData[mapGridIndexY][mapGridIndexX] != 0;
}

bool Map::IsInside(vec2 pos)
{
    return pos.x >= 0 && pos.x <= MAP_NUM_COLS * TILE_SIZE && pos.y >= 0 && pos.y <= MAP_NUM_ROWS * TILE_SIZE;
}

int32_t Map::GetAt(int32_t i, int32_t j)
{
    return m_mapData[i][j];
}