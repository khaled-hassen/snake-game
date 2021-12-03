#include "apple.h"
#include <stdlib.h>
#include "../utils/math/math.h"
#include "../../debug/debug.h"

Apple* Apple_Create()
{
    Apple* apple = (Apple*) malloc(sizeof(Apple));
    if (apple == NULL)
    {
        LOG_ERROR("Cannot create apple");
        return NULL;
    }

    apple->shape.w = APPLE_SIZE;
    apple->shape.h = APPLE_SIZE;
    apple->lastPosition.x = -1;
    apple->lastPosition.y = -1;

    return apple;
}

// helper function to check the collision between the apple and a list of shapes
// bool detectShapesCollision(Apple* apple, RectList* shapes)
// {
//     if (shapes == NULL) return false;
//
//     for (; shapes != NULL; shapes = shapes->next)
//         if (Math_detectCollision(apple->shape, shapes->shape)) return true;
//
//     return false;
// }

void Apple_generatePosition(Apple* apple, SDL_Rect area, SDL_Rect head)
{
    // get the number of horizontal and vertical cells contained in the area
    int hCells = area.w / CELL_SIZE;
    int vCells = area.h / CELL_SIZE;

    // get from which xCell and yCell the area starts
    int xCells = area.x / CELL_SIZE;
    int yCells = area.y / CELL_SIZE;

    // generate a random cell x and y used to spawn the apple (different from last position)
    // also the apple must not collide with the snake
    int randomX = 0, randomY = 0;
    SDL_Rect rect = apple->shape;
    do
    {
        randomX = Math_randomInt(xCells, hCells + xCells - 1) * CELL_SIZE;
        randomY = Math_randomInt(yCells, vCells + yCells - 1) * CELL_SIZE;
        rect.x = randomX;
        rect.y = randomY;
    } while ((randomX == apple->lastPosition.x) && (randomY == apple->lastPosition.y) ||
             Math_detectCollision(rect, head));
    // || detectShapesCollision(apple, shapes)

    apple->shape.x = randomX;
    apple->shape.y = randomY;
    apple->lastPosition.x = randomX;
    apple->lastPosition.y = randomY;
}

void Apple_draw(SDL_Surface* screen, Apple* apple)
{
    SDL_FillRect(screen, &apple->shape, SDL_MapRGB(screen->format, 0xFF, 0, 0));
}

void Apple_Destroy(Apple* apple) { free(apple); }
