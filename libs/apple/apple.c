#include "apple.h"
#include "../utils/math/math.h"

SDL_Rect Apple_spawn(SDL_Rect area)
{
    // get the number of horizontal and vertical cells
    int hCells = area.w / CELL_SIZE;
    int vCells = area.h / CELL_SIZE;

    // generate a random cell x and y used to spawn the apple
    int randomX = Math_randomInt(1, hCells) * CELL_SIZE;
    int randomY = Math_randomInt(1, vCells) * CELL_SIZE;

    SDL_Rect apple = { randomX, randomY, APPLE_SIZE, APPLE_SIZE };
    return apple;
}

void Apple_draw(SDL_Surface* screen, SDL_Rect apple)
{
    SDL_FillRect(screen, &apple, SDL_MapRGB(screen->format, 0xFF, 0, 0));
}
