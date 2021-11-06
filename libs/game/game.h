#pragma once

#include <SDL/SDL.h>
#include <stdbool.h>

#define MAX_FPS 60

#define SCREEN_HEIGHT 580
#define SCREEN_WIDTH 720
#define WALL_THICKNESS 15

#define START_X WALL_THICKNESS
#define START_Y WALL_THICKNESS

typedef Uint32 Timer;

SDL_Surface* Game_init();

Timer Game_getTicks();

Timer Game_getFPS(Timer frameTime);

void Game_capFPS(Timer frameTime);

void Game_drawBoard(SDL_Surface* screen);

void Game_update(SDL_Surface* screen);

bool Game_exit(SDL_Event* event);

void Game_close();