#pragma once

#include <SDL/SDL.h>
#include "../utils/types.h"

#define SNAKE_WIDTH 15
#define SNAKE_BASE_SPEED 100

typedef struct Snake
{
    SDL_Rect shape;
    int length;
    int speed;
    Vector velocity;
} Snake;

Snake* Snake_createSnake(int x, int y);

void Snake_moveSnake(SDL_Surface* screen, Snake* snake, Vector direction, Timer fps);

void Snake_destroySnake(Snake* snake);