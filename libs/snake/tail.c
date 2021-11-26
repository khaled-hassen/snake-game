#include "tail.h"

RectList* Tail_create(int x, int y, int length, int width)
{
    RectList* tail = NULL;
    RectList* tmp = NULL;
    // create the tail backward (the head of the linked list is located at the end of the snake)
    for (int i = length; i > 0; --i)
    {
        SDL_Rect shape = { x + width * (length - i), y, width, width };
        RectList* chunk = (RectList*) malloc(sizeof(RectList));
        chunk->shape = shape;
        chunk->next = NULL;

        if (tail == NULL) tail = chunk;
        else tmp->next = chunk;

        tmp = chunk;
    }
    return tail;
}

void Tail_destroy(RectList* tail)
{
    while (tail != NULL)
    {
        RectList* tmp = tail->next;
        free(tail);
        tail = tmp;
    }
}

void Tail_render(SDL_Surface* screen, RectList* tail, Uint32 color)
{
    for (; tail != NULL; tail = tail->next) SDL_FillRect(screen, &tail->shape, color);
}

void Tail_move(RectList* tail, Vector velocity)
{
    for (; tail != NULL; tail = tail->next)
    {
        tail->shape.x += velocity.x;
        tail->shape.y += velocity.y;
    }
}

RectList* Tail_increment(RectList* tail)
{
    RectList* newTail = (RectList*) malloc(sizeof(RectList));
    SDL_Rect shape = { tail->shape.x - tail->shape.w, tail->shape.y, tail->shape.w, tail->shape.h };
    newTail->shape = shape;
    newTail->next = tail;
    return newTail;
}
