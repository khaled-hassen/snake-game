#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "../utils/config.h"

typedef enum
{
    SINGLE = 0, MULTI, QUIT, NONE
} GameMode;

// create the main menu items and stores them
void GameMode_createMenuItems(SDL_Rect items[3]);

// draws the game menu
void GameMode_drawMenu(SDL_Surface* screen, TTF_Font* font, SDL_Rect menuItems[3], int score);

// get the game selected mode by handling the user mouse input
// return the selected game mode
GameMode GameMode_getMode(SDL_Rect menuItems[3], SDL_Event event);