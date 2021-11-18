#pragma once

#ifdef DEBUG

#define LOG_ERROR(error) fprintf(stderr, "[ERROR] %s\n", error)
#define LOG_SDL_ERROR(error) fprintf(stderr, "[ERROR] %s\n[SDL ERROR] %s\n", error, SDL_GetError())
#define LOG_TTF_ERROR(error) fprintf(stderr, "[ERROR] %s\n[TTF ERROR] %s\n", error, TTF_GetError())

#define DEBUG_BOARD(screen, area) \
int rows = area.h / CELL_SIZE;\
int columns = area.w / CELL_SIZE;\
Uint32 c2C394B = SDL_MapRGB(screen->format, 0x2C, 0x39, 0x4B);\
Uint32 c787A91 = SDL_MapRGB(screen->format, 0x78, 0x7A, 0x91);\
for (int i = 0; i < rows; ++i) \
{\
    for (int j = 0; j < columns; ++j) \
    {\
    SDL_Rect rowRect = { area.x + j * CELL_SIZE, area.y + i * CELL_SIZE, CELL_SIZE, CELL_SIZE };\
    SDL_FillRect(screen, &rowRect, (i + j) % 2 == 0 ? c2C394B : c787A91);\
    }\
}

#define DEBUG_FPS(frameTime) \
char debugMsg[10]; \
sprintf(debugMsg, "FPS: %d", (1000 / (SDL_GetTicks() - frameTime)));\
SDL_WM_SetCaption(debugMsg, NULL);

#else

#define LOG_ERROR(error)
#define LOG_SDL_ERROR(error)
#define LOG_TTF_ERROR(error)
#define DEBUG_FPS(frameTime, score)
#define DEBUG_BOARD(screen, area)

#endif
