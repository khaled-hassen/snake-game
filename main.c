#include "libs/game/game.h"
#include "libs/snake/snake.h"
#include "libs/apple/apple.h"
#include "libs/utils/math/math.h"

int main(int argc, char* argv[])
{
    SDL_Surface* screen = Game_init();
    if (screen == NULL) return 1;

    Snake* snake = Snake_createSnake(START_X, START_Y);
    if (snake == NULL) return 1;

    // TODO remove
    char msg[100] = "";

    SDL_Rect walls[4];
    Timer frameTime = 0;
    SDL_Event event;
    bool quit = false;
    bool gameOver = false;
    Vector direction;
    SDL_Rect movingArea = Game_drawBoard(screen, walls);
    SDL_Rect apple = Apple_spawn(movingArea);
    int frames = 0;

    // needs to be initialized in order to randomly generate the apples
    Math_initSeed();
    while (true)
    {
        while (Game_getEvents(&event)) quit = Game_exited(event);
        if (quit) break;

        frames++;
        frameTime = Game_getTicks();
        movingArea = Game_drawBoard(screen, walls);
        Apple_draw(screen, apple);

        if (Snake_detectCollision(snake, apple))
        {
            Snake_increaseScore(snake);
            apple = Apple_spawn(movingArea);
        }

        if (!gameOver) direction = Game_handleInput(event);
        else Snake_stop(snake);

        Snake_turn(snake, direction);
        Snake_moveSnake(screen, snake, frames);
        gameOver = Snake_hitWalls(snake, walls);

        Game_update(screen);
        Game_capFPS(frameTime);
        // to prevent the frames value from overflowing
        frames %= MAX_FPS;

        // TODO remove
        sprintf(msg, "FPS: %d   Score: %d", Game_getFPS(frameTime), snake->score);
        SDL_WM_SetCaption(msg, NULL);
    }

    Snake_destroySnake(snake);
    Game_close();

    return 0;
}
