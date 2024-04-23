#ifndef MAP_H
#define MAP_H

#include <cstdint>
#include <memory>
#include "display.h"
#include "vec2.h"

#define MAP_NUM_ROWS 13
#define MAP_NUM_COLS 20

class Map
{
public:
    void Render(const std::shared_ptr<Display> &display);

    bool HasWallAt(vec2 pos);
    bool IsInside(vec2 pos);
    int32_t GetAt(int32_t i, int32_t j);

protected:
    static int32_t m_mapData[MAP_NUM_ROWS][MAP_NUM_COLS];
};

#endif