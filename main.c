#include "libs/game/game.h"
#include "libs/snake/snake.h"
#include "libs/apple/apple.h"
#include "libs/utils/math/math.h"
#include "debug/debug.h"

int main(int argc, char* argv[])
{
    Game game = Game_init();
    if (game.screen == NULL) return 1;

    SDL_Rect walls[4];
    SDL_Rect movingArea = Game_drawBoard(game.screen, walls);

    Snake* snake = Snake_create(movingArea.x, movingArea.y);
    if (snake == NULL) return 1;

    Apple* apple = Apple_Create();
    if (apple == NULL) return 1;

    bool quit = false;
    bool gameOver = false;
    Vector direction;

    Timer frameTime = 0;
    int frames = 0;
    SDL_Event event;

    // needs to be initialized in order to randomly generate the apples
    Math_initSeed();
    Apple_generatePosition(apple, movingArea);

    // TODO remove
    Snake_move(game.screen, snake, 1);


    while (true)
    {
        while (Game_getEvents(&event)) quit = Game_exited(event);
        if (quit) break;

        frames++;
        frameTime = Game_getTicks();
        // movingArea = Game_drawBoard(game.screen, walls);
        // DEBUG_BOARD(game.screen, movingArea);
        Apple_draw(game.screen, apple);

        if (Snake_detectCollision(snake, apple->shape))
        {
            Snake_eat(snake);
            Apple_generatePosition(apple, movingArea);
        }
        Apple_generatePosition(apple, movingArea);

        if (!gameOver) direction = Game_handleInput(event);
        else Snake_stop(snake);

        Snake_turn(snake, direction);
        // Snake_move(game.screen, snake, frames);
        gameOver = Snake_hitWalls(snake, walls);

        Game_renderScore(game, snake->score);
        Game_update(game.screen);
        Game_capFPS(frameTime);
        // to prevent the frames value from overflowing
        frames %= MAX_FPS;

        DEBUG_FPS(frameTime);
    }

    Snake_destroy(snake);
    Apple_Destroy(apple);
    Game_close(game);

    return 0;
}
