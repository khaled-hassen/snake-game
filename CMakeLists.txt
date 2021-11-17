cmake_minimum_required(VERSION 3.20)
project(snake C)

set(CMAKE_C_STANDARD 99)

add_executable(${PROJECT_NAME} main.c debug/debug.h libs/game/game.c libs/game/game.h libs/snake/snake.c libs/snake/snake.h libs/utils/types.h libs/apple/apple.c libs/apple/apple.h libs/utils/math/math.c libs/utils/math/math.h libs/utils/config.h)
target_link_libraries(${PROJECT_NAME} -lmingw32 -lSDLmain -lSDL -mwindows)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG=1)
endif()
