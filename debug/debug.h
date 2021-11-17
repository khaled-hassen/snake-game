#pragma once

#ifdef DEBUG

#define LOG_ERROR(error) fprintf(stderr, "[ERROR] %s\n", error)
#define LOG_SDL_ERROR(error) fprintf(stderr, "[ERROR] %s\n[SDL ERROR] %s\n", error, SDL_GetError())

#define DEBUG_FPS_SCORE(frameTime, score) \
char debugMsg[100]; \
sprintf(debugMsg, "FPS: %d   Score: %d", (1000 / (SDL_GetTicks() - frameTime)), score);\
SDL_WM_SetCaption(debugMsg, NULL);

#else

#define LOG_ERROR(error)
#define LOG_SDL_ERROR(error)
#define GET_FPS(frameTime)

#endif
