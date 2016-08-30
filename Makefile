CC=g++
FILES=src/main.cpp src/shaders.cpp src/game.cpp src/floor.cpp src/player.cpp src/map.cpp
LINK=-lGL -lglfw -lGLEW -lSOIL
OPTIONS=-DGLEW_STATIC -Iheaders


all:
	$(CC) $(FILES) $(LINK) $(OPTIONS)