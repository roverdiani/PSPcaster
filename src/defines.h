#ifndef DEFINES_H
#define DEFINES_H

#define M_PI 3.14159265358979323846264338327950288

#define TILE_SIZE 64
#define MINIMAP_SCALE_FACTOR 0.1

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 272

#define FOV_ANGLE (60 * (M_PI / 180))
#define DIST_PROJ_PLANE ((SCREEN_WIDTH / 2) / tanf(FOV_ANGLE / 2))

#define FPS 30
#define MILLISECS_PER_FRAME (1000 / FPS)

#endif