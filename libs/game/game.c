#include "game.h"
#include <stdio.h>
#include <math.h>
#include "../../debug/debug.h"

Game Game_init()
{
    Game game = { NULL, NULL, NULL };

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        LOG_SDL_ERROR("Cannot Game_init SDL");
        return game;
    }

    if (TTF_Init() < 0)
    {
        LOG_TTF_ERROR("Cannot init SDL_TTF");
        return game;
    }

    // to spawn the window at the center
    setenv("SDL_VIDEO_CENTERED", "SDL_VIDEO_CENTERED", 1);
    SDL_Surface* screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, SDL_SWSURFACE);
    if (screen == NULL) LOG_SDL_ERROR("Cannot create screen");
    SDL_WM_SetCaption("Snake game", NULL);

    TTF_Font* font = TTF_OpenFont("robot.ttf", 28);
    if (font == NULL) LOG_TTF_ERROR("Cannot open font");

    game.screen = screen;
    game.font = font;

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

void Game_close(Game game)
{
    TTF_CloseFont(game.font);
    SDL_FreeSurface(game.message);
    SDL_Quit();
}

void Game_renderScore(Game game, int score)
{
    char msg[100];
    sprintf(msg, "Score: %d", score);
    SDL_Color color = { 0xFF, 0xFF, 0xFF };
    game.message = TTF_RenderText_Solid(game.font, msg, color);
    if (game.message == NULL)
    {
        LOG_TTF_ERROR("Cannot render message");
        return;
    }

    SDL_Rect offset = { 10, 10, 100, 30 };
    SDL_BlitSurface(game.message, NULL, game.screen, &offset);
}

void Game_update(Game game)
{
    if (SDL_Flip(game.screen) < 0) LOG_SDL_ERROR("Cannot update screen");
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

    SDL_Rect topWall = { 0, 0, SCREEN_WIDTH, 5 * WALL_THICKNESS };
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

    SDL_Rect movingArea = { walls[LEFT].w, walls[TOP].h, SCREEN_WIDTH - walls[LEFT].w - walls[RIGHT].w,
                            SCREEN_HEIGHT - walls[TOP].h - walls[BOTTOM].h };
    return movingArea;
}

// helper function to draw menu items
void drawItems(Game game)
{
    char* items[] = { "Single player", "Multi player", "Quit" };
    int itemWidth = 250, itemHeight = 80;
    int itemsGap = itemHeight + 50;
    int startY = 150;
    SDL_Color color = { 0, 0, 0 };
    for (int i = 0; i < 3; ++i)
    {
        SDL_Rect item = { SCREEN_WIDTH / 2 - itemWidth / 2, startY + itemsGap * i, itemWidth, itemHeight };
        SDL_Surface* message = TTF_RenderText_Solid(game.font, items[i], color);
        if (message == NULL)
        {
            LOG_TTF_ERROR("Cannot render message");
            return;
        }

        SDL_FillRect(game.screen, &item, SDL_MapRGB(game.screen->format, 0xFA, 0xED, 0xF0));
        SDL_Rect offset2 = { SCREEN_WIDTH / 2 - message->clip_rect.w / 2,
                             item.y + item.h / 2 - message->clip_rect.h / 2,
                             message->clip_rect.w, message->clip_rect.h };
        SDL_BlitSurface(message, NULL, game.screen, &offset2);
    }
}

void Game_drawMenu(Game game)
{
    SDL_Color color = { 0xFF, 0xFF, 0xFF };
    SDL_Surface* message = TTF_RenderText_Solid(game.font, "Snake game", color);
    if (message == NULL)
    {
        LOG_TTF_ERROR("Cannot render message");
        return;
    }

    SDL_FillRect(game.screen, NULL, SDL_MapRGB(game.screen->format, 48, 48, 48));
    // Draw game name
    SDL_Rect offset = { SCREEN_WIDTH / 2 - message->clip_rect.w / 2, 50, message->clip_rect.w, message->clip_rect.h };
    SDL_BlitSurface(message, NULL, game.screen, &offset);

    drawItems(game);
}
