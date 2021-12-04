#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <stdbool.h>
#include "gameMode.h"
#include "../utils/types.h"
#include "../utils/config.h"

#define WALL_THICKNESS CELL_SIZE

typedef Uint32 Timer;

typedef struct
{
    SDL_Surface* screen;
    TTF_Font* font;
    SDL_Surface* scoreMessage;
    GameMode mode;
} Game;

// initialize the game and sdl_ttf
// returns the game screen and font
Game* Game_init();

// return the time since the game starts in ms
Timer Game_getTicks();

// cap the game's fps to prevent over-rendering
void Game_capFPS(Timer frameTime);

// draw the game board
// return the board moving area and store the walls variables
SDL_Rect Game_drawBoard(Game* game, SDL_Rect walls[4]);

// render the snake score
void Game_renderScore(Game* game, int score);

// render changes
void Game_update(Game* game);

// get keyboard events
// return the number of events
int Game_getEvents(SDL_Event* event);

// handle the user keyboard input
// return the input direction: UP DOWN LEFT RIGHT
Vector Game_handleKeyboardInput(SDL_Event event);

// check if the user closes the game or not
// return the state
bool Game_exited(SDL_Event event);

// close the game and free the allocated memory
void Game_close(Game** game);

// saves the snake's best score
void Game_saveBestScore(int score);