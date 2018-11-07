#!/bin/bash
if [ ! -d "./build" ]; then
	mkdir build
fi

gcc -pthread common.c message.c game.c map.c player.c server.c -o build/server.out
