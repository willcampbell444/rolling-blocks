CC=g++
FILES=src/main.cpp src/shaders.cpp src/game.cpp src/floor.cpp src/player.cpp src/map.cpp src/heightMap.cpp
LINK=-lGL -lglfw -lGLEW -lSOIL
OPTIONS=-DGLEW_STATIC -Iheaders -g


all:
	$(CC) $(FILES) $(LINK) $(OPTIONS)