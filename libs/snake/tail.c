#include "tail.h"

Tail* Tail_create(int x, int y, int length, int width)
{
    Tail* tail = NULL;
    Tail* tmp = NULL;
    // create the tail backward (the head of the linked list is located at the end of the snake)
    for (int i = length; i > 0; --i)
    {
        SDL_Rect shape = { x + width * (length - i), y, width, width };
        Tail* chunk = (Tail*) malloc(sizeof(Tail));
        chunk->shape = shape;
        chunk->next = NULL;

        if (tail == NULL) tail = chunk;
        else tmp->next = chunk;

        tmp = chunk;
    }
    return tail;
}

void Tail_destroy(Tail* tail)
{
    while (tail != NULL)
    {
        Tail* tmp = tail->next;
        free(tail);
        tail = tmp;
    }
}

void Tail_render(SDL_Surface* screen, Tail* tail, Uint32 color)
{
    for (; tail != NULL; tail = tail->next) SDL_FillRect(screen, &tail->shape, color);
}

void Tail_move(Tail* tail, Vector velocity)
{
    for (; tail != NULL; tail = tail->next)
    {
        tail->shape.x += velocity.x;
        tail->shape.y += velocity.y;
    }
}

Tail* Tail_increment(Tail* tail)
{
    Tail* newTail = (Tail*) malloc(sizeof(Tail));
    SDL_Rect shape = { tail->shape.x - tail->shape.w, tail->shape.y, tail->shape.w, tail->shape.h };
    newTail->shape = shape;
    newTail->next = tail;
    return newTail;
}
