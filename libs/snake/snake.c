#include "snake.h"
#include "stdlib.h"
#include "../utils/math/math.h"
#include "../../debug/debug.h"


Snake* Snake_create(int x, int y)
{
    Snake* snake = (Snake*) malloc(sizeof(Snake));
    if (snake == NULL)
    {
        LOG_ERROR("Cannot create snake");
        return NULL;
    }

    snake->tail = Tail_create(x, y, SNAKE_WIDTH);
    Vector velocity = { SNAKE_BASE_SPEED, 0 };
    snake->velocity = velocity;
    SDL_Rect head = { x + SNAKE_WIDTH * snake->tail->length, y, SNAKE_WIDTH, SNAKE_WIDTH };
    snake->head = head;
    snake->score = 0;

    return snake;
}

void Snake_destroy(Snake* snake)
{
    Tail_destroy(snake->tail);
    free(snake);
}

void Snake_move(SDL_Surface* screen, Snake* snake, int frames)
{
    // if (1/CELLS_PER_SECOND) has passed move the snake
    if ((frames % (MAX_FPS / CELLS_PER_SECOND)) == 0)
    {
        Tail_move(snake->head, snake->tail);
        snake->head.x += snake->velocity.x;
        snake->head.y += snake->velocity.y;
    }
    Uint32 color = SDL_MapRGB(screen->format, 0, 0xFF, 0);
    SDL_FillRect(screen, &snake->head, color);
    Tail_render(screen, snake->tail, color);
}

void Snake_turn(Snake* snake, Vector direction)
{
    // to prevent the snake from going back on his tail
    if ((direction.x == 1 || direction.x == -1) && snake->tail->blocks[0].y == snake->head.y) return;
    if ((direction.y == 1 || direction.y == -1) && snake->tail->blocks[0].x == snake->head.x) return;

    if (direction.x != 0 || direction.y != 0)
    {
        // change the snake velocity which depends on speed and direction
        snake->velocity.x = SNAKE_BASE_SPEED * direction.x;
        snake->velocity.y = SNAKE_BASE_SPEED * direction.y;
    }
}

// helper function detects if the snake hits a wall or not
bool detectWallsCollision(Snake* snake, SDL_Rect* walls)
{
    if ((snake->head.x >= (walls[LEFT].x + walls[LEFT].w))
        && ((snake->head.x + snake->head.w) <= walls[RIGHT].x)
        && (snake->head.y >= (walls[TOP].y + walls[TOP].h))
        && ((snake->head.y + snake->head.h) <= walls[BOTTOM].y))
        return false;

    return true;
}

// helper function detects if the snake hits his tail or not
bool detectTailCollision(Snake* snake)
{
    for (int i = 0; i < snake->tail->length; ++i)
        if (Math_detectCollision(snake->head, snake->tail->blocks[i])) return true;
    return false;
}

bool Snake_isDead(Snake* snake, SDL_Rect* walls)
{
    return detectWallsCollision(snake, walls) || detectTailCollision(snake);
}

void Snake_eat(Snake* snake)
{
    snake->score += 10;
    Tail_increment(snake->tail);
}