#include "libs/game/game.h"
#include "libs/snake/snake.h"

int main(int argc, char* argv[])
{
    SDL_Surface* screen = Game_init();
    if (screen == NULL) return 1;

    Snake* snake = Snake_createSnake(START_X, START_Y);
    if (snake == NULL) return 1;

    // TODO remove
    char msg[100] = "";

    Timer frameTime = 0;
    Timer fps = MAX_FPS;
    SDL_Event event;
    bool quit = false;

    while (true)
    {
        while (Game_getEvents(&event)) quit = Game_exited(event);
        if (quit) break;

        frameTime = Game_getTicks();
        Game_drawBoard(screen);

        Vector direction = Game_handleInput(event);
        Snake_moveSnake(screen, snake, direction, fps);
        Game_update(screen);

        Game_capFPS(frameTime);

        // TODO remove
        sprintf(msg, "%d", fps);
        SDL_WM_SetCaption(msg, NULL);

        fps = Game_getFPS(frameTime);
    }

    Snake_destroySnake(snake);
    Game_close();

    return 0;
}
