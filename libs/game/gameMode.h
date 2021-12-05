#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "../utils/config.h"

typedef enum
{
    GM_SINGLE = 0, GM_MULTI, GM_QUIT, GM_NONE
} GameMode;

// create the main menu items and store them
void GameMode_createMenuItems(SDL_Rect items[3]);

// draw the game menu and best scores and last scores
void GameMode_drawMenu(SDL_Surface* screen, TTF_Font* font, SDL_Rect menuItems[3], int score1, int score2);

// get the selected game mode by handling the user mouse input
// return the game mode
GameMode GameMode_getMode(SDL_Rect menuItems[3], SDL_Event event);