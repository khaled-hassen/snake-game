#pragma once

#include <SDL/SDL.h>

#define SNAKE_WIDTH 15
#define SNAKE_BASE_SPEED 1

typedef Uint32 Timer;

typedef struct Snake
{
    SDL_Rect shape;
    int length;
    int speed;
} Snake;

Snake* Snake_createSnake(int x, int y);

void Snake_moveSnake(SDL_Surface* screen, Snake* snake, Timer fps);

void Snake_destroySnake(Snake* snake);