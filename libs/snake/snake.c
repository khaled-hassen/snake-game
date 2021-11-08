#include <math.h>
#include "snake.h"
#include "stdlib.h"
#include "../utils/logs.h"

Snake* Snake_createSnake(int x, int y)
{
    Snake* snake = (Snake*) malloc(sizeof(Snake));
    if (snake == NULL)
    {
        LOG_ERROR("Cannot create snake");
        return NULL;
    }

    snake->length = 1;
    Vector velocity = { SNAKE_BASE_SPEED, 0 };
    snake->velocity = velocity;
    snake->speed = SNAKE_BASE_SPEED;
    SDL_Rect shape = { x, y, SNAKE_WIDTH, SNAKE_WIDTH };
    snake->shape = shape;

    return snake;
}

void Snake_destroySnake(Snake* snake)
{
    free(snake);
}

void Snake_moveSnake(SDL_Surface* screen, Snake* snake, Vector direction, Timer fps)
{
    Uint32 color = SDL_MapRGB(screen->format, 0, 0xFF, 0);

    if (direction.x != 0 || direction.y != 0)
    {
        snake->velocity.x = snake->speed * direction.x;
        snake->velocity.y = snake->speed * direction.y;
    }

    Sint16 deltaX = (Sint16) round((double) snake->velocity.x / fps);
    Sint16 deltaY = (Sint16) round((double) snake->velocity.y / fps);

    snake->shape.x += deltaX;
    snake->shape.y += deltaY;

    SDL_FillRect(screen, &snake->shape, color);
}
