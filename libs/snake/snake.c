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
    snake->score = 0;

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
        // change the snake velocity which depends on speed and direction
        snake->velocity.x = snake->speed * direction.x;
        snake->velocity.y = snake->speed * direction.y;
    }
    else
    {
        // keep the velocity in sync with speed
        if (snake->velocity.x != 0)
            snake->velocity.x = snake->velocity.x > 0 ? snake->speed : -snake->speed;

        if (snake->velocity.y != 0)
            snake->velocity.y = snake->velocity.y > 0 ? snake->speed : -snake->speed;
    }

    // get the x and y movement per frame
    Sint16 deltaX = (Sint16) round((double) snake->velocity.x / fps);
    Sint16 deltaY = (Sint16) round((double) snake->velocity.y / fps);

    snake->shape.x += deltaX;
    snake->shape.y += deltaY;

    SDL_FillRect(screen, &snake->shape, color);
}

bool Snake_detectCollision(Snake* snake, SDL_Rect other)
{
    if ((snake->shape.x + snake->shape.w <= other.x)
        || (snake->shape.x >= other.x + other.w)
        || (snake->shape.y + snake->shape.h <= other.y)
        || (snake->shape.y >= other.y + other.h))
        return false;

    return true;
}

bool Snake_hitWalls(Snake* snake, SDL_Rect* walls)
{
    if ((snake->shape.x >= (walls[LEFT].x + walls[LEFT].w))
        && ((snake->shape.x + snake->shape.w) <= walls[RIGHT].x)
        && (snake->shape.y >= (walls[TOP].y + walls[TOP].h))
        && ((snake->shape.y + snake->shape.h) <= walls[BOTTOM].y))
        return false;

    return true;
}

void Snake_stop(Snake* snake)
{
    snake->velocity.x = 0;
    snake->velocity.y = 0;
}

void Snake_increaseScore(Snake* snake)
{
    snake->score += 10;
    snake->speed = snake->speed > MAX_SNAKE_SPEED ? MAX_SNAKE_SPEED : snake->speed + 10;
}
