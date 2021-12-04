#include "game.h"
#include <stdio.h>
#include <math.h>
#include "../utils/math/math.h"
#include "../../debug/debug.h"

Game* Game_init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        LOG_SDL_ERROR("Cannot Game_init SDL");
        return NULL;
    }

    if (TTF_Init() < 0)
    {
        LOG_TTF_ERROR("Cannot init SDL_TTF");
        return NULL;
    }

    Game* game = (Game*) malloc(sizeof(Game));
    game->scoreMessage = NULL;
    game->mode = GM_NONE;

    // to spawn the window at the center
    setenv("SDL_VIDEO_CENTERED", "SDL_VIDEO_CENTERED", 1);
    SDL_Surface* screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, SDL_SWSURFACE);
    if (screen == NULL) LOG_SDL_ERROR("Cannot create screen");
    SDL_WM_SetCaption("Snake game", NULL);

    TTF_Font* font = TTF_OpenFont("robot.ttf", 28);
    if (font == NULL) LOG_TTF_ERROR("Cannot open font");

    game->screen = screen;
    game->font = font;

    return game;
}

Timer Game_getTicks() { return SDL_GetTicks(); }

void Game_capFPS(Timer frameTime)
{
    // limit the game frames per seconds
    Timer deltaTime = SDL_GetTicks() - frameTime;
    double frameRenderTime = 1000.0 / MAX_FPS;
    if (deltaTime < frameRenderTime) SDL_Delay(floor(frameRenderTime - deltaTime));
}

void Game_close(Game** game)
{
    TTF_CloseFont((*game)->font);
    SDL_FreeSurface((*game)->scoreMessage);
    SDL_Quit();
    free(*game);
    *game = NULL;
}

void Game_renderScore(Game* game, int score)
{
    char msg[100];
    sprintf(msg, "Score: %d", score);
    SDL_Color color = { 0xFF, 0xFF, 0xFF };
    game->scoreMessage = TTF_RenderText_Solid(game->font, msg, color);
    if (game->scoreMessage == NULL)
    {
        LOG_TTF_ERROR("Cannot render scoreMessage");
        return;
    }

    SDL_Rect offset = { 10, 10, 100, 30 };
    SDL_BlitSurface(game->scoreMessage, NULL, game->screen, &offset);
}

void Game_update(Game* game)
{
    if (SDL_Flip(game->screen) < 0) LOG_SDL_ERROR("Cannot update screen");
}

int Game_getEvents(SDL_Event* event) { return SDL_PollEvent(event); }

bool Game_exited(SDL_Event event) { return event.type == SDL_QUIT; }

Vector Game_handleKeyboardInput(SDL_Event event)
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

SDL_Rect Game_drawBoard(Game* game, SDL_Rect walls[4])
{
    SDL_FillRect(game->screen, NULL, SDL_MapRGB(game->screen->format, 0, 0, 0));

    // drawing the walls
    Uint32 wallColor = SDL_MapRGB(game->screen->format, 48, 48, 48);

    SDL_Rect topWall = { 0, 0, SCREEN_WIDTH, 5 * WALL_THICKNESS };
    SDL_FillRect(game->screen, &topWall, wallColor);

    SDL_Rect bottomWall = { 0, SCREEN_HEIGHT - WALL_THICKNESS, SCREEN_WIDTH, WALL_THICKNESS };
    SDL_FillRect(game->screen, &bottomWall, wallColor);

    SDL_Rect leftWall = { 0, 0, WALL_THICKNESS, SCREEN_HEIGHT };
    SDL_FillRect(game->screen, &leftWall, wallColor);

    SDL_Rect rightWall = { SCREEN_WIDTH - WALL_THICKNESS, 0, WALL_THICKNESS, SCREEN_HEIGHT };
    SDL_FillRect(game->screen, &rightWall, wallColor);

    walls[P_TOP] = topWall;
    walls[P_BOTTOM] = bottomWall;
    walls[P_LEFT] = leftWall;
    walls[P_RIGHT] = rightWall;

    SDL_Rect movingArea = { walls[P_LEFT].w, walls[P_TOP].h, SCREEN_WIDTH - walls[P_LEFT].w - walls[P_RIGHT].w,
                            SCREEN_HEIGHT - walls[P_TOP].h - walls[P_BOTTOM].h };
    return movingArea;
}

void Game_saveBestScore(int score)
{
    char* filename = "save.txt";
    FILE* fp = fopen(filename, "r");
    int bestScore = 0;
    if (fp == NULL || fscanf(fp, "%d", &bestScore) != 1) bestScore = 0; // set the best score to 0 if there isn't one
    fclose(fp);
    fp = fopen(filename, "w");
    fprintf(fp, "%d", score > bestScore ? score : bestScore);
    fclose(fp);
}
