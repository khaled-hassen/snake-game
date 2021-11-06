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
    SDL_Event event;
    while (!Game_exit(&event))
    {
        frameTime = Game_getTicks();
        Game_drawBoard(screen);
        Snake_moveSnake(screen, snake, Game_getFPS(frameTime));
        Game_update(screen);

        Game_capFPS(frameTime);

        // TODO remove
        sprintf(msg, "%d", Game_getFPS(frameTime));
        SDL_WM_SetCaption(msg, NULL);
    }

    Snake_destroySnake(snake);
    Game_close();

    return 0;
}
