#include "math.h"
#include <stdlib.h>
#include <time.h>

void Math_initSeed() { srand(time(0)); }

int Math_randomInt(int start, int end)
{
    return (rand() % (end - start + 1)) + start;
}

