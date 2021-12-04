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
    char* labels[] = { "Single player", "Multi player", "Quit" };
    SDL_Color color = { 0, 0, 0 };
    for (int i = 0; i < 3; ++i)
    {
        SDL_Surface* message = TTF_RenderText_Solid(font, labels[i], color);
        if (message == NULL)
        {
            LOG_TTF_ERROR("Cannot render scoreMessage");
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
int getBestScore()
{
    FILE* fp = fopen("save.txt", "r");
    if (fp == NULL) return 0;
    int bestScore = 0;
    if (fscanf(fp, "%d", &bestScore) != 1) bestScore = 0; // set the best score to 0 if there isn't one
    fclose(fp);
    return bestScore;
}

void GameMode_drawMenu(SDL_Surface* screen, TTF_Font* font, SDL_Rect menuItems[3], int score)
{
    SDL_Color color = { 0xFF, 0xFF, 0xFF };
    SDL_Surface* title = TTF_RenderText_Solid(font, "Snake game", color);
    if (title == NULL)
    {
        LOG_TTF_ERROR("Cannot render scoreMessage");
        return;
    }
    SDL_Rect titleOffset = { SCREEN_WIDTH / 3 - title->clip_rect.w / 3, 50,
                             title->clip_rect.w, title->clip_rect.h };

    char scoreMsg[20] = "";
    sprintf(scoreMsg, "Score: %d", score);
    SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, scoreMsg, color);
    if (scoreSurface == NULL)
    {
        LOG_TTF_ERROR("Cannot render scoreMessage");
        return;
    }
    SDL_Rect scoreOffset = { 5 * SCREEN_WIDTH / 6 - 5 * scoreSurface->clip_rect.w / 6, 50,
                             scoreSurface->clip_rect.w, scoreSurface->clip_rect.h };

    char bestScore[20] = "";
    sprintf(bestScore, "Best Score: %d", getBestScore());
    SDL_Surface* bestScoreSurface = TTF_RenderText_Solid(font, bestScore, color);
    if (bestScoreSurface == NULL)
    {
        LOG_TTF_ERROR("Cannot render scoreMessage");
        return;
    }
    SDL_Rect bestScoreOffset = { 5 * SCREEN_WIDTH / 6 - 5 * bestScoreSurface->clip_rect.w / 6,
                                 80 + scoreSurface->clip_rect.h,
                                 bestScoreSurface->clip_rect.w, bestScoreSurface->clip_rect.h };

    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 48, 48, 48));
    // Display the game's title
    SDL_BlitSurface(title, NULL, screen, &titleOffset);
    // Display the game's saved best score
    SDL_BlitSurface(bestScoreSurface, NULL, screen, &bestScoreOffset);
    // Display the player's Score
    SDL_BlitSurface(scoreSurface, NULL, screen, &scoreOffset);

    drawItems(screen, font, menuItems);
}
