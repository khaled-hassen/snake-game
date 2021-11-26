#include "math.h"
#include <stdlib.h>
#include <time.h>

void Math_initSeed() { srand(time(0)); }

int Math_randomInt(int start, int end) { return (rand() % (end - start + 1)) + start; }

bool Math_detectCollision(SDL_Rect shape, SDL_Rect other)
{
    if ((shape.x + shape.w <= other.x)
        || (shape.x >= other.x + other.w)
        || (shape.y + shape.h <= other.y)
        || (shape.y >= other.y + other.h))
        return false;

    return true;
}

