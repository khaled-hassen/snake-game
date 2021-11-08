#include "apple.h"
#include "../utils/math/math.h"

void Apple_generate(SDL_Surface* screen, SDL_Rect area)
{
    int endX = area.x + area.w - APPLE_DIM;
    int endY = area.y + area.h - APPLE_DIM;

    int randomX = Math_randomInt(area.x, endX);
    int randomY = Math_randomInt(area.y, endY);

    Uint32 color = SDL_MapRGB(screen->format, 0xFF, 0, 0);
    SDL_Rect apple = {randomX, randomY, APPLE_DIM, APPLE_DIM};
    SDL_FillRect(screen, &apple, color);
}
