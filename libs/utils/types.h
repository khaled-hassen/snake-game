#pragma once

typedef struct
{
    int x;
    int y;
} Vector;

typedef enum
{
    P_TOP, P_BOTTOM, P_LEFT, P_RIGHT
} Position;

typedef enum {
    O_RIGHT = 1, O_LEFT = -1
} Orientation;