#include "tail.h"

Tail* Tail_create(int x, int y, int width)
{
    Tail* tail = (Tail*) malloc(sizeof(Tail));
    tail->length = TAIL_INITIAL_LENGTH;
    tail->blocks = (SDL_Rect*) malloc(tail->length * sizeof(SDL_Rect));
    // create the blocks backward (the head of the linked list is located at the end of the snake)
    for (int i = 0; i < tail->length; ++i)
    {
        SDL_Rect shape = { x + width * i, y, width, width };
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

void Tail_move(Tail* tail, Vector velocity)
{
    for (int i = 0; i < tail->length; ++i)
    {
        tail->blocks[i].x += velocity.x;
        tail->blocks[i].y += velocity.y;
    }
}

void Tail_increment(Tail* tail)
{
    // TODO fix: the snake starts incrementing only after eating 4 apples
    SDL_Rect lastBlock = tail->blocks[tail->length - 1];
    SDL_Rect shape = { lastBlock.x - lastBlock.w, lastBlock.y, lastBlock.w, lastBlock.h };
    tail->blocks[tail->length++] = shape;
}
