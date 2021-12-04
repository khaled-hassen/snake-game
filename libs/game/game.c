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
    game->player1Score = NULL;
    game->player2Score = NULL;
    game->mode = GM_NONE;

    // to spawn the window at the center
    setenv("SDL_VIDEO_CENTERED", "SDL_VIDEO_CENTERED", 1);
    SDL_Surface* screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, SDL_SWSURFACE);
    if (screen == NULL) LOG_SDL_ERROR("Cannot create screen");
    SDL_WM_SetCaption("Snake game", NULL);

    TTF_Font* font = TTF_OpenFont("robot.ttf", 25);
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
    SDL_FreeSurface((*game)->player1Score);
    SDL_Quit();
    free(*game);
    *game = NULL;
}

void Game_renderScore(Game* game, int score1, int score2)
{
    char msg1[50] = "";
    sprintf(msg1, "Player 1 score: %d", score1);
    SDL_Color color = { 0xFF, 0xFF, 0xFF };
    game->player1Score = TTF_RenderText_Solid(game->font, msg1, color);
    if (game->player1Score == NULL)
    {
        LOG_TTF_ERROR("Cannot render player1Score");
        return;
    }

    char msg2[50] = "";
    if (score2 != -1)
    {
        sprintf(msg2, "Player 2 score: %d", score2);
        game->player2Score = TTF_RenderText_Solid(game->font, msg2, color);
        if (game->player2Score == NULL)
        {
            LOG_TTF_ERROR("Cannot render player1Score");
            return;
        }
    }

    SDL_Rect offset = { 10, 10, 100, 30 };
    SDL_BlitSurface(game->player1Score, NULL, game->screen, &offset);

    if (score2 != -1)
    {
        offset.x = offset.w + 100;
        SDL_BlitSurface(game->player2Score, NULL, game->screen, &offset);
    }
}

void Game_update(Game* game)
{
    if (SDL_Flip(game->screen) < 0) LOG_SDL_ERROR("Cannot update screen");
}

int Game_getEvents(SDL_Event* event) { return SDL_PollEvent(event); }

bool Game_exited(SDL_Event event) { return event.type == SDL_QUIT; }

// Helper functions to get the direction
Vector getUpDirection()
{
    Vector direction = { 0, -1 };
    return direction;
}

Vector getDownDirection()
{
    Vector direction = { 0, 1 };
    return direction;
}


Vector getLeftDirection()
{
    Vector direction = { -1, 0 };
    return direction;
}

Vector getRightDirection()
{
    Vector direction = { 1, 0 };
    return direction;
}
//

Vector Game_handleKeyboardInput(SDL_Event event, bool second)
{
    Vector direction = { 0, 0 };
    if (event.type != SDL_KEYDOWN) return direction;

    if (second)
        switch (event.key.keysym.sym)
        {
            case SDLK_UP:
                direction = getUpDirection();
                break;
            case SDLK_DOWN:
                direction = getDownDirection();
                break;
            case SDLK_LEFT:
                direction = getLeftDirection();
                break;
            case SDLK_RIGHT:
                direction = getRightDirection();
                break;
            default:
                break;
        }
    else
        switch (event.key.keysym.sym)
        {
            case SDLK_w:
                direction = getUpDirection();
                break;
            case SDLK_s:
                direction = getDownDirection();
                break;
            case SDLK_a:
                direction = getLeftDirection();
                break;
            case SDLK_d:
                direction = getRightDirection();
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

void Game_saveBestScores(int score1, int score2)
{
    char* filename = "save.txt";
    FILE* fp = fopen(filename, "r");
    int bestScore1 = 0, bestScore2 = 0;
    // set the best scores to 0 if there aren't one
    if (fp == NULL || fscanf(fp, "%d,%d", &bestScore1, &bestScore2) != 2) bestScore1 = bestScore2 = 0;

    fclose(fp);
    fp = fopen(filename, "w");
    fprintf(fp, "%d,%d", score1 > bestScore1 ? score1 : bestScore1, score2 > bestScore2 ? score2 : bestScore2);
    fclose(fp);
}
