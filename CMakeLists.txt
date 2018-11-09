cmake_minimum_required(VERSION 3.12)
project(server C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

find_package (Threads)

add_executable(server
        src/common.c
        src/common.h
        src/game.c
        src/game.h
        src/map.c
        src/map.h
        src/message.c
        src/message.h
        src/player.c
        src/player.h
        src/server.c
        src/server.h
        src/types.h)

add_executable(client
        src/common.c
        src/common.h
        src/message.c
        src/message.h
        src/client.c
)

target_link_libraries (server ${CMAKE_THREAD_LIBS_INIT})