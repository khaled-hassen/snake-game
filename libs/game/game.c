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

Timer Game_getTicks() { return SDL_GetTicks(); }

Timer Game_getFPS(Timer frameTime)
{
    Timer deltaTime = Game_getTicks() - frameTime;
    return floor(1000.0 / deltaTime);
}

void Game_capFPS(Timer frameTime)
{
    // limit the game frames per seconds
    Timer deltaTime = SDL_GetTicks() - frameTime;
    double frameRenderTime = 1000.0 / MAX_FPS;
    if (deltaTime < frameRenderTime) SDL_Delay(floor(frameRenderTime - deltaTime));
}

void Game_close() { SDL_Quit(); }

void Game_update(SDL_Surface* screen)
{
    if (SDL_Flip(screen) < 0) LOG_SDL_ERROR("Cannot update screen");
}

int Game_getEvents(SDL_Event* event) { return SDL_PollEvent(event); }

bool Game_exited(SDL_Event event) { return event.type == SDL_QUIT; }

Vector Game_handleInput(SDL_Event event)
{
    Vector direction = { 0, 0 };
    if (event.type != SDL_KEYDOWN) return direction;

    switch (event.key.keysym.sym)
    {
        case SDLK_w:
            direction.x = 0;
            direction.y = -1;
            break;

        case SDLK_s:
            direction.x = 0;
            direction.y = 1;
            break;

        case SDLK_a:
            direction.x = -1;
            direction.y = 0;
            break;

        case SDLK_d:
            direction.x = 1;
            direction.y = 0;
            break;
        default:
            break;
    }

    return direction;
}

SDL_Rect Game_drawBoard(SDL_Surface* screen, SDL_Rect walls[4])
{
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

    walls[TOP] = topWall;
    walls[BOTTOM] = bottomWall;
    walls[LEFT] = leftWall;
    walls[RIGHT] = rightWall;

    SDL_Rect movingArea = { WALL_THICKNESS, WALL_THICKNESS, SCREEN_WIDTH - 2 * WALL_THICKNESS,
                            SCREEN_HEIGHT - 2 * WALL_THICKNESS };

    /*TODO remove*/
    int rows = movingArea.h / CELL_SIZE;
    int columns = movingArea.w / CELL_SIZE;
    Uint32 c2C394B = SDL_MapRGB(screen->format, 0x2C, 0x39, 0x4B);
    Uint32 c787A91 = SDL_MapRGB(screen->format, 0x78, 0x7A, 0x91);

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            SDL_Rect rowRect = { movingArea.x + j * CELL_SIZE, movingArea.y + i * CELL_SIZE, CELL_SIZE, CELL_SIZE };
            SDL_FillRect(screen, &rowRect, (i + j) % 2 == 0 ? c2C394B : c787A91);
        }
    }
    /*TODO remove*/
    return movingArea;
}






