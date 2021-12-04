#include "tail.h"

Tail* Tail_create(int x, int y, int width, Orientation ori)
{
    Tail* tail = (Tail*) malloc(sizeof(Tail));
    tail->length = TAIL_INITIAL_LENGTH;
    tail->blocks = (SDL_Rect*) malloc(MAX_TAIL_INITIAL_LENGTH * sizeof(SDL_Rect));
    for (int i = 0; i < tail->length; ++i)
    {
        int mult = (ori == O_LEFT) ? (i + 1) : (tail->length - i - 1);
        SDL_Rect shape = { x + width * mult, y, width, width };
        tail->blocks[i] = shape;
    }
    return tail;
}

void Tail_destroy(Tail* tail)
{
    free(tail->blocks);
    free(tail);
}

void Tail_render(SDL_Surface* screen, Tail* tail, Uint32 color)
{
    for (int i = 0; i < tail->length; ++i)
        SDL_FillRect(screen, &tail->blocks[i], color);
}

void Tail_move(SDL_Rect head, Tail* tail)
{
    for (int i = tail->length - 1; i > 0; --i)
        tail->blocks[i] = tail->blocks[i - 1];
    tail->blocks[0] = head;
}

void Tail_increment(Tail* tail)
{
    if (tail->length >= MAX_TAIL_INITIAL_LENGTH) return;

    SDL_Rect lastBlock = tail->blocks[tail->length - 1];
    SDL_Rect shape = { lastBlock.x, lastBlock.y, lastBlock.w, lastBlock.h };
    tail->blocks[tail->length++] = shape;
}
