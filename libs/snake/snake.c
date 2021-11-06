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
    snake->speed = SNAKE_BASE_SPEED;
    SDL_Rect shape = { x, y, SNAKE_WIDTH, SNAKE_WIDTH };
    snake->shape = shape;

    return snake;
}

void Snake_destroySnake(Snake* snake)
{
    free(snake);
}

void Snake_moveSnake(SDL_Surface* screen, Snake* snake)
{
    Uint32 color = SDL_MapRGB(screen->format, 0, 0xFF, 0);
    snake->shape.x += snake->speed;
    SDL_FillRect(screen, &snake->shape, color);
}
