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

    Snake* snake1 = NULL;
    Snake* snake2 = NULL;
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
        if (game->mode == GM_NONE) game->mode = GameMode_getMode(menuItems, event);
        quit = quit || game->mode == GM_QUIT;
        if (quit) break;

        frames++;
        frameTime = Game_getTicks();
        if (game->mode == GM_NONE) GameMode_drawMenu(game->screen, game->font, menuItems, score);
        else
        {
            if (snake1 == NULL)
            {
                snake1 = Snake_create(movingArea.x, movingArea.y, game->screen, O_RIGHT);
                if (snake1 == NULL) return 1;
            }

            if (game->mode == GM_MULTI && snake2 == NULL)
            {
                snake2 = Snake_create(movingArea.w + movingArea.x, movingArea.h + movingArea.y, game->screen, O_LEFT);
                if (snake2 == NULL) return 1;
            }

            if (apple == NULL)
            {
                apple = Apple_Create();
                if (apple == NULL) return 1;
                Apple_generatePosition(apple, movingArea, snake1, snake2);
            }

            movingArea = Game_drawBoard(game, walls);
            DEBUG_BOARD(game->screen, movingArea);
            Apple_draw(game->screen, apple);

            if (Math_detectCollision(snake1->head, apple->shape))
            {
                Snake_eat(snake1);
                Apple_generatePosition(apple, movingArea, snake1, snake2);
            }

            if (snake2 != NULL && Math_detectCollision(snake2->head, apple->shape))
            {
                Snake_eat(snake2);
                Apple_generatePosition(apple, movingArea, snake1, snake2);
            }

            snake1->direction = Game_handleKeyboardInput(event, false);
            Snake_turn(snake1);
            Snake_move(game->screen, snake1, frames);

            if (snake2 != NULL)
            {
                snake2->direction = Game_handleKeyboardInput(event, true);
                Snake_turn(snake2);
                Snake_move(game->screen, snake2, frames);
            }

            if (Snake_isDead(snake1, snake2, walls) || (snake2 != NULL && Snake_isDead(snake2, snake1, walls)))
            {
                // TODO update to handle snake 2
                game->mode = GM_NONE;
                score = snake1->score;
                Game_saveBestScore(snake1->score);
                Snake_destroy(&snake1);
                if (snake2 != NULL) Snake_destroy(&snake2);
                Apple_destroy(&apple);
            }
            else Game_renderScore(game, snake1->score);
        }

        frames %= MAX_FPS;
        Game_update(game);
        Game_capFPS(frameTime);
        DEBUG_FPS(frameTime);
    }

    Game_close(&game);

    return 0;
}
