#include "snake.h"
#include "stdlib.h"
#include "../../debug/debug.h"
#include "tail.h"


Snake* Snake_create(int x, int y)
{
    Snake* snake = (Snake*) malloc(sizeof(Snake));
    if (snake == NULL)
    {
        LOG_ERROR("Cannot create snake");
        return NULL;
    }

    snake->length = SNAKE_INITIAL_LENGTH;
    snake->speed = SNAKE_SPEED;
    Vector velocity = { snake->speed, 0 };
    snake->velocity = velocity;
    SDL_Rect head = { x + SNAKE_WIDTH * snake->length, y, SNAKE_WIDTH, SNAKE_WIDTH };
    snake->head = head;
    snake->score = 0;
    snake->tail = Tail_create(x, y, snake->length, SNAKE_WIDTH);

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
        snake->head.x += snake->velocity.x;
        snake->head.y += snake->velocity.y;
        Tail_move(snake->tail, snake->velocity);
    }
    Uint32 color = SDL_MapRGB(screen->format, 0, 0xFF, 0);
    SDL_FillRect(screen, &snake->head, color);
    Tail_render(screen, snake->tail, color);
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

bool Snake_hitWalls(Snake* snake, SDL_Rect* walls)
{
    if ((snake->head.x >= (walls[LEFT].x + walls[LEFT].w))
        && ((snake->head.x + snake->head.w) <= walls[RIGHT].x)
        && (snake->head.y >= (walls[TOP].y + walls[TOP].h))
        && ((snake->head.y + snake->head.h) <= walls[BOTTOM].y))
        return false;

    return true;
}

void Snake_stop(Snake* snake)
{
    snake->velocity.x = 0;
    snake->velocity.y = 0;
}

void Snake_eat(Snake* snake)
{
    snake->score += 10;
    snake->length += 1;
    snake->tail = Tail_increment(snake->tail);
}