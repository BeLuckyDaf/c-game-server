cmake_minimum_required(VERSION 3.12)
project(server C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

find_package (Threads)

add_executable(server
        common.c
        common.h
        game.c
        game.h
        map.c
        map.h
        message.c
        message.h
        player.c
        player.h
        server.c
        server.h
        types.h)

add_executable(client
        common.c
        common.h
        message.c
        message.h
        client.c
)

target_link_libraries (server ${CMAKE_THREAD_LIBS_INIT})