#include "gameMode.h"
#include "../../debug/debug.h"

void GameMode_createMenuItems(SDL_Rect items[3])
{
    int itemWidth = 250, itemHeight = 80;
    int itemsGap = itemHeight + 50;
    int startY = 150;
    for (int i = 0; i < 3; ++i)
    {
        SDL_Rect item = { SCREEN_WIDTH / 3 - itemWidth / 3, startY + itemsGap * i, itemWidth, itemHeight };
        items[i] = item;
    }
}

GameMode GameMode_getMode(SDL_Rect menuItems[3], SDL_Event event)
{
    if (event.type != SDL_MOUSEBUTTONDOWN) return GM_NONE;

    int x = event.motion.x, y = event.motion.y;
    for (GameMode i = GM_SINGLE; i < GM_NONE; ++i) // GM_NONE is 3
    {
        if (x >= menuItems[i].x && x <= (menuItems[i].x + menuItems[i].w)
            && y >= menuItems[i].y && y <= (menuItems[i].y + menuItems[i].h))
            return i;
    }
    return GM_NONE;
}

// helper function to draw menu items
void drawItems(SDL_Surface* screen, TTF_Font* font, SDL_Rect menuItems[3])
{
    char* labels[] = { "Single player", "Multiplayer", "Quit" };
    SDL_Color color = { 0, 0, 0 };
    for (int i = 0; i < 3; ++i)
    {
        SDL_Surface* message = TTF_RenderText_Solid(font, labels[i], color);
        if (message == NULL)
        {
            LOG_TTF_ERROR("Cannot render player1Score");
            return;
        }
        SDL_FillRect(screen, &menuItems[i], SDL_MapRGB(screen->format, 0xFA, 0xED, 0xF0));
        SDL_Rect offset = { menuItems[i].x + menuItems[i].w / 2 - message->clip_rect.w / 2,
                            menuItems[i].y + menuItems[i].h / 2 - message->clip_rect.h / 2,
                            message->clip_rect.w, message->clip_rect.h };
        SDL_BlitSurface(message, NULL, screen, &offset);
    }
}

// helper function to get the saved best score
void getBestScores(int* score1, int* score2)
{
    FILE* fp = fopen("save.txt", "r");
    if (fp == NULL) return;
    int bestScore1 = 0, bestScore2 = 0;
    if (fscanf(fp, "%d,%d", &bestScore1, &bestScore2) != 2) bestScore1 = bestScore2 = 0;
    fclose(fp);
    *score1 = bestScore1;
    *score2 = bestScore2;
}

// Helper function to display the game title
void displayTitle(SDL_Surface* screen, TTF_Font* font)
{
    SDL_Color color = { 0xFF, 0xFF, 0xFF };
    SDL_Surface* title = TTF_RenderText_Solid(font, "Snake game", color);
    if (title == NULL)
    {
        LOG_TTF_ERROR("Cannot render game title");
        return;
    }
    SDL_Rect titleOffset = { SCREEN_WIDTH / 3 - title->clip_rect.w / 3, 50,
                             title->clip_rect.w, title->clip_rect.h };
    SDL_BlitSurface(title, NULL, screen, &titleOffset);
}

// Helper function to display score
void displayScore(SDL_Surface* screen, TTF_Font* font, char* msg, int score, int y)
{
    SDL_Color color = { 0xFF, 0xFF, 0xFF };

    char scoreMsg[50] = "";
    sprintf(scoreMsg, "%s: %d", msg, score);
    SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, scoreMsg, color);
    if (scoreSurface == NULL)
    {
        LOG_TTF_ERROR("Cannot render message");
        return;
    }

    SDL_Rect offset = { 5 * SCREEN_WIDTH / 6 - 5 * scoreSurface->clip_rect.w / 6, y,
                        scoreSurface->clip_rect.w, scoreSurface->clip_rect.h };

    SDL_BlitSurface(scoreSurface, NULL, screen, &offset);
}

void GameMode_drawMenu(SDL_Surface* screen, TTF_Font* font, SDL_Rect menuItems[3], int score1, int score2)
{
    int bestScore1 = 0, bestScore2 = 0;
    getBestScores(&bestScore1, &bestScore2);

    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 48, 48, 48));
    displayTitle(screen, font);
    displayScore(screen, font, "Player1 score", score1, 50);
    displayScore(screen, font, "Player1 best score", bestScore1, 100);
    displayScore(screen, font, "Player2 score", score2, 150);
    displayScore(screen, font, "Player2 best score", bestScore2, 200);

    drawItems(screen, font, menuItems);
}
