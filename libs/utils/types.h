#pragma once

#include <SDL/SDL_video.h>

typedef struct RectList
{
    SDL_Rect shape;
    struct RectList* next;
} RectList;

typedef struct
{
    int x;
    int y;
} Vector;

typedef enum
{
    TOP, BOTTOM, LEFT, RIGHT
} Position;