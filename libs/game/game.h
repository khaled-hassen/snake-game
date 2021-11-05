#pragma once
#include <SDL/SDL.h>
#include <stdbool.h>

#define SCREEN_HEIGHT 580
#define SCREEN_WIDTH 720
#define WALL_THICKNESS 15

SDL_Surface* Game_init();

void Game_drawBoard(SDL_Surface* screen);

void Game_update(SDL_Surface* screen);

bool Game_exit(SDL_Event* event);

void Game_close();