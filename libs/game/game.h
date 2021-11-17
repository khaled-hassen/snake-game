#pragma once

#include <SDL/SDL.h>
#include <stdbool.h>
#include "../utils/types.h"
#include "../utils/config.h"

#define SCREEN_WIDTH (H_CELLS * CELL_SIZE)
#define SCREEN_HEIGHT (V_CELLS * CELL_SIZE)

#define WALL_THICKNESS CELL_SIZE
#define START_X WALL_THICKNESS
#define START_Y WALL_THICKNESS

// initialize the game
// returns the game screen
SDL_Surface* Game_init();

// return the time since the game starts in ms
Timer Game_getTicks();

// cap the game's fps to prevent over-rendering
void Game_capFPS(Timer frameTime);

// draw the game board
// return the walls and the board moving area
SDL_Rect Game_drawBoard(SDL_Surface* screen, SDL_Rect walls[4]);

// render changes
void Game_update(SDL_Surface* screen);

// get keyboard events
// return the number of events
int Game_getEvents(SDL_Event* event);

// handle the user input
// return the input direction: UP DOWN LEFT RIGHT
Vector Game_handleInput(SDL_Event event);

// check if the user closes the game or not
// return the state
bool Game_exited(SDL_Event event);

// close the game and free the allocated memory
void Game_close();