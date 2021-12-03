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
    Vector direction;

    Timer frameTime = 0;
    int frames = 0;
    SDL_Event event;

    // needs to be initialized in order to randomly generate the apples
    Math_initSeed();
    Apple_generatePosition(apple, movingArea, snake);

    while (true)
    {
        while (Game_getEvents(&event)) quit = Game_exited(event);
        if (quit) break;

        frames++;
        frameTime = Game_getTicks();
        movingArea = Game_drawBoard(game.screen, walls);
        DEBUG_BOARD(game.screen, movingArea);
        Apple_draw(game.screen, apple);

        if (Math_detectCollision(snake->head, apple->shape))
        {
            Snake_eat(snake);
            Apple_generatePosition(apple, movingArea, snake);
        }

        direction = Game_handleInput(event);

        Snake_turn(snake, direction);
        Snake_move(game.screen, snake, frames);

        if (Snake_isDead(snake, walls)) break;

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
