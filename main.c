#include "libs/game/game.h"
#include "libs/utils/math/math.h"
#include "debug/debug.h"
#include "libs/snake/snake.h"
#include "libs/apple/apple.h"

int main(int argc, char* argv[])
{
    Game* game = Game_init();
    if (game == NULL || game->screen == NULL) return 1;

    SDL_Rect walls[4];
    SDL_Rect movingArea = Game_drawBoard(game, walls);

    Snake* snake = NULL;
    Apple* apple = NULL;
    int frames = 0;

    SDL_Rect menuItems[3];
    GameMode_createMenuItems(menuItems);

    bool quit = false;
    Timer frameTime = 0;
    SDL_Event event;
    int score = 0;

    // needs to be initialized in order to randomly generate the apples
    Math_initSeed();

    while (true)
    {
        while (Game_getEvents(&event)) quit = Game_exited(event);
        if (game->mode == NONE) game->mode = GameMode_getMode(menuItems, event);
        quit = quit || game->mode == QUIT;
        if (quit) break;

        frames++;
        frameTime = Game_getTicks();
        if (game->mode == NONE) GameMode_drawMenu(game->screen, game->font, menuItems, score);
        else
        {
            if (snake == NULL)
            {
                snake = Snake_create(movingArea.x, movingArea.y);
                if (snake == NULL) return 1;
            }

            if (apple == NULL)
            {
                apple = Apple_Create();
                if (apple == NULL) return 1;
                Apple_generatePosition(apple, movingArea, snake);
            }

            movingArea = Game_drawBoard(game, walls);
            DEBUG_BOARD(game->screen, movingArea);
            Apple_draw(game->screen, apple);

            if (Math_detectCollision(snake->head, apple->shape))
            {
                Snake_eat(snake);
                Apple_generatePosition(apple, movingArea, snake);
            }

            snake->direction = Game_handleKeyboardInput(event);
            Snake_turn(snake);
            Snake_move(game->screen, snake, frames);

            if (Snake_isDead(snake, walls))
            {
                game->mode = NONE;
                score = snake->score;
                Game_saveBestScore(snake->score);
                Snake_destroy(&snake);
                Apple_destroy(&apple);
            }
            else Game_renderScore(game, snake->score);
        }

        frames %= MAX_FPS;
        Game_update(game);
        Game_capFPS(frameTime);
        DEBUG_FPS(frameTime);
    }

    Game_close(&game);

    return 0;
}
