#pragma once

#include <SDL/SDL.h>

#define SNAKE_WIDTH 15
#define SNAKE_BASE_SPEED 10

typedef struct Snake
{
    SDL_Rect shape;
    int length;
    int speed;
} Snake;

Snake* Snake_createSnake(int x, int y);

void Snake_moveSnake(SDL_Surface* screen, Snake* snake);

void Snake_destroySnake(Snake* snake);