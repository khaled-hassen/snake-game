#include "libs/game/game.h"
#include "libs/snake/snake.h"

int main(int argc, char* argv[])
{
    SDL_Surface* screen = Game_init();
    if (screen == NULL) return 1;

    Snake* snake = Snake_createSnake(START_X, START_Y);
    if (snake == NULL) return 1;

    Timer update = 0;
    SDL_Event event;
    while (!Game_exit(&event))
    {
        update = Game_getTick();
        Game_drawBoard(screen);
        Snake_moveSnake(screen, snake);
        Game_update(screen);

        Game_capFPS(update);
    }

    Snake_destroySnake(snake);
    Game_close();

    return 0;
}
