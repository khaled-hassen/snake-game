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

typedef enum
{
    SINGLE = 0, MULTI, QUIT, NONE
} MenuItem;

typedef struct
{
    SDL_Surface* screen;
    TTF_Font* font;
    SDL_Surface* scoreMessage;
    SDL_Rect menuItems[3];
} Game;

// initialize the game and sdl_ttf
// returns the game screen and font
Game* Game_init();

// return the time since the game starts in ms
Timer Game_getTicks();

// cap the game's fps to prevent over-rendering
void Game_capFPS(Timer frameTime);

// draw the game board
// return the board moving area
SDL_Rect Game_drawBoard(Game* game, SDL_Rect walls[4]);

// draws the game menu
void Game_drawMenu(Game* game);

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

// handle the user mouse input
// return the selected menu item
MenuItem Game_handleMouseInput(Game* game, SDL_Event event);

// check if the user closes the game or not
// return the state
bool Game_exited(SDL_Event event);

// close the game and free the allocated memory
void Game_close(Game* game);