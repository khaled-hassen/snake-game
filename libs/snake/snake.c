#include "snake.h"
#include "stdlib.h"
#include "../utils/math/math.h"
#include "../../debug/debug.h"


Snake* Snake_create(int x, int y, SDL_Surface* screen, Orientation ori)
{
    Snake* snake = (Snake*) malloc(sizeof(Snake));
    if (snake == NULL)
    {
        LOG_ERROR("Cannot create snake");
        return NULL;
    }

    int headX = x + ((ori == O_LEFT) ? -SNAKE_WIDTH * (TAIL_INITIAL_LENGTH + 1) : SNAKE_WIDTH * TAIL_INITIAL_LENGTH);
    int headY = y - (ori == O_LEFT ? SNAKE_WIDTH : 0);

    snake->color = SDL_MapRGB(screen->format, ori == O_LEFT ? 0xFF : 0, 0xFF, 0);
    snake->tail = Tail_create((ori == O_LEFT) ? headX : x, headY, SNAKE_WIDTH, ori);
    Vector velocity = { ori * SNAKE_BASE_SPEED, 0 };
    Vector direction = { ori, 0 };
    snake->velocity = velocity;
    snake->direction = direction;

    SDL_Rect head = { headX, headY, SNAKE_WIDTH, SNAKE_WIDTH };
    snake->head = head;
    snake->score = 0;

    return snake;
}

void Snake_destroy(Snake** snake)
{
    Tail_destroy((*snake)->tail);
    free(*snake);
    *snake = NULL;
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
    SDL_FillRect(screen, &snake->head, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));
    Tail_render(screen, snake->tail, snake->color);
}

void Snake_turn(Snake* snake)
{
    // to prevent the snake from going back on his tail
    if ((snake->direction.x == 1 || snake->direction.x == -1) && snake->tail->blocks[0].y == snake->head.y) return;
    if ((snake->direction.y == 1 || snake->direction.y == -1) && snake->tail->blocks[0].x == snake->head.x) return;

    if (snake->direction.x != 0 || snake->direction.y != 0)
    {
        // change the snake velocity which depends on speed and direction
        snake->velocity.x = SNAKE_BASE_SPEED * snake->direction.x;
        snake->velocity.y = SNAKE_BASE_SPEED * snake->direction.y;
    }
}

// helper function detects if the snake hits a wall or not
bool detectWallsCollision(Snake* snake, SDL_Rect* walls)
{
    if ((snake->head.x >= (walls[P_LEFT].x + walls[P_LEFT].w))
        && ((snake->head.x + snake->head.w) <= walls[P_RIGHT].x)
        && (snake->head.y >= (walls[P_TOP].y + walls[P_TOP].h))
        && ((snake->head.y + snake->head.h) <= walls[P_BOTTOM].y))
        return false;

    return true;
}

// helper function detects if the snake hits his tail or the other snake's tail (if provided)
bool detectTailCollision(Snake* snake, Snake* other)
{
    int length = other == NULL ? snake->tail->length : other->tail->length;
    SDL_Rect* blocks = other == NULL ? snake->tail->blocks : other->tail->blocks;
    for (int i = 0; i < length; ++i)
        if (Math_detectCollision(snake->head, blocks[i])) return true;
    return false;
}

bool Snake_isDead(Snake* snake, Snake* other, SDL_Rect* walls)
{
    return detectWallsCollision(snake, walls) || detectTailCollision(snake, NULL) ||
           (other != NULL && detectTailCollision(snake, other)) ||
           (other != NULL && Math_detectCollision(snake->head, other->head));
}

void Snake_eat(Snake* snake)
{
    snake->score += 10;
    Tail_increment(snake->tail);
}