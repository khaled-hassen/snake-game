#pragma once

#include <SDL/SDL.h>
#include <stdbool.h>
#include "../utils/types.h"
#include "../utils/config.h"

#define SNAKE_WIDTH CELL_SIZE
#define SNAKE_BASE_SPEED 100
#define MAX_SNAKE_SPEED 400

typedef struct Snake
{
    SDL_Rect shape;
    int length;
    int score;
    int speed;
    Vector velocity;
} Snake;

// create the snake
Snake* Snake_createSnake(int x, int y);

// move the snake according the direction
void Snake_moveSnake(SDL_Surface* screen, Snake* snake, Vector direction, Timer fps);

// free the snake from memory
void Snake_destroySnake(Snake* snake);

// check if snake collides with other or not
// return result
bool Snake_detectCollision(Snake* snake, SDL_Rect other);

// increases the snake's score (normally when he eats an apple)
void Snake_increaseScore(Snake* snake);

// check if the snake hits a wall or not
// return the state
bool Snake_hitWalls(Snake* snake, SDL_Rect* walls);

// stop the snake's movement
void Snake_stop(Snake* snake);

