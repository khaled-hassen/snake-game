#include <math.h>
#include "snake.h"
#include "stdlib.h"
#include "../../debug/debug.h"

Snake* Snake_createSnake(int x, int y)
{
    Snake* snake = (Snake*) malloc(sizeof(Snake));
    if (snake == NULL)
    {
        LOG_ERROR("Cannot create snake");
        return NULL;
    }

    snake->length = 1;
    snake->speed = CELL_SIZE;
    Vector velocity = { snake->speed, 0 };
    snake->velocity = velocity;
    SDL_Rect shape = { x, y, SNAKE_WIDTH, SNAKE_WIDTH };
    snake->shape = shape;
    snake->score = 0;

    return snake;
}

void Snake_destroySnake(Snake* snake)
{
    free(snake);
}

void Snake_moveSnake(SDL_Surface* screen, Snake* snake, int frames)
{
    // if (1/CELLS_PER_SECOND) has passed move the snake
    if ((frames % (MAX_FPS / CELLS_PER_SECOND)) == 0)
    {
        snake->shape.x += snake->velocity.x;
        snake->shape.y += snake->velocity.y;
    }
    SDL_FillRect(screen, &snake->shape, SDL_MapRGB(screen->format, 0, 0xFF, 0));
}

void Snake_turn(Snake* snake, Vector direction)
{
    if (direction.x != 0 || direction.y != 0)
    {
        // change the snake velocity which depends on speed and direction
        snake->velocity.x = snake->speed * direction.x;
        snake->velocity.y = snake->speed * direction.y;
    }
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
}