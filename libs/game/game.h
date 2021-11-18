#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <stdbool.h>
#include "../utils/types.h"
#include "../utils/config.h"

#define SCREEN_WIDTH (WIDTH_IN_CELLS * CELL_SIZE)
#define SCREEN_HEIGHT (HEIGHT_IN_CELLS * CELL_SIZE)

#define WALL_THICKNESS CELL_SIZE

typedef Uint32 Timer;

typedef struct {
    SDL_Surface* screen;
    TTF_Font* font;
    SDL_Surface* message;
} Game;

// initialize the game and sdl_ttf
// returns the game screen and font
Game Game_init();

// return the time since the game starts in ms
Timer Game_getTicks();

// cap the game's fps to prevent over-rendering
void Game_capFPS(Timer frameTime);

// draw the game board
// return the walls and the board moving area
SDL_Rect Game_drawBoard(SDL_Surface* screen, SDL_Rect walls[4]);

// render the snake score
void Game_renderScore(Game game, int score);

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
void Game_close(Game game);