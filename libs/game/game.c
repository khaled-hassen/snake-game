#include "game.h"
#include <stdio.h>
#include <math.h>
#include "../utils/logs.h"

SDL_Surface* Game_init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        LOG_SDL_ERROR("Cannot Game_init SDL");
        return NULL;
    }

    SDL_Surface* screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, SDL_SWSURFACE);
    if (screen == NULL) LOG_SDL_ERROR("Cannot create screen");
    SDL_WM_SetCaption("Snake game", NULL);

    return screen;
}

Timer Game_getTick() { return SDL_GetTicks(); }

void Game_capFPS(Timer timer)
{
    double deltaTime = SDL_GetTicks() - timer;
    double frameRenderTime = 1000.0 / MAX_FPS;
    if (deltaTime < frameRenderTime) SDL_Delay(floor(frameRenderTime - deltaTime));
}

void Game_close() { SDL_Quit(); }

void Game_update(SDL_Surface* screen)
{
    if (SDL_Flip(screen) < 0) LOG_SDL_ERROR("Cannot update screen");
}

bool Game_exit(SDL_Event* event)
{
    while (SDL_PollEvent(event)) if (event->type == SDL_QUIT) return true;
    return false;
}


void Game_drawBoard(SDL_Surface* screen)
{
    // draws the game grid
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

    // drawing the walls
    Uint32 wallColor = SDL_MapRGB(screen->format, 48, 48, 48);

    SDL_Rect topWall = { 0, 0, SCREEN_WIDTH, WALL_THICKNESS };
    SDL_FillRect(screen, &topWall, wallColor);

    SDL_Rect bottomWall = { 0, SCREEN_HEIGHT - WALL_THICKNESS, SCREEN_WIDTH, WALL_THICKNESS };
    SDL_FillRect(screen, &bottomWall, wallColor);

    SDL_Rect leftWall = { 0, 0, WALL_THICKNESS, SCREEN_HEIGHT };
    SDL_FillRect(screen, &leftWall, wallColor);

    SDL_Rect rightWall = { SCREEN_WIDTH - WALL_THICKNESS, 0, WALL_THICKNESS, SCREEN_HEIGHT };
    SDL_FillRect(screen, &rightWall, wallColor);
}


