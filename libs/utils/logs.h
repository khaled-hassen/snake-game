#pragma once

#define LOG_SDL_ERROR(error) fprintf(stderr, "[ERROR] %s\n[SDL ERROR] %s\n", error, SDL_GetError())
