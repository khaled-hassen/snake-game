#pragma once

#include <SDL/SDL.h>
#include <stdbool.h>
#include "../utils/types.h"

#define MAX_FPS 60

#define SCREEN_HEIGHT 580
#define SCREEN_WIDTH 720
#define WALL_THICKNESS 15

#define START_X WALL_THICKNESS
#define START_Y WALL_THICKNESS

SDL_Surface* Game_init();

Timer Game_getTicks();

Timer Game_getFPS(Timer frameTime);

void Game_capFPS(Timer frameTime);

void Game_drawBoard(SDL_Surface* screen);

void Game_update(SDL_Surface* screen);

int Game_getEvents(SDL_Event* event);

Vector Game_handleInput(SDL_Event event);

bool Game_exited(SDL_Event event);

void Game_close();