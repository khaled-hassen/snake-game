#include "libs/game/game.h"
#include "libs/snake/snake.h"
#include "libs/apple/apple.h"
#include "libs/utils/math/math.h"
#include "debug/debug.h"

int main(int argc, char* argv[])
{
    Game game = Game_init();
    if (game.screen == NULL) return 1;

    bool quit = false;
    Timer frameTime = 0;
    SDL_Event event;

    while (true)
    {
        while (Game_getEvents(&event)) quit = Game_exited(event);
        if (quit) break;

        frameTime = Game_getTicks();
        Game_drawMenu(game);
        Game_update(game);
        Game_capFPS(frameTime);
        DEBUG_FPS(frameTime);
    }
    Game_close(game);

    return 0;
}
