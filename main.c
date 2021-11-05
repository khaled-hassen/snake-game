#include "libs/game/game.h"

int main(int argc, char* argv[])
{
    SDL_Surface* screen = Game_init();
    if (screen == NULL) return 1;

    SDL_Event event;
    while (!Game_exit(&event))
    {
        Game_drawBoard(screen);
        Game_update(screen);
    }

    Game_close();

    return 0;
}
