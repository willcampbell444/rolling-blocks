CC=g++
FILES=src/main.cpp src/shaders.cpp src/game.cpp src/floor.cpp src/player.cpp src/map.cpp src/heightMap.cpp src/menu.cpp src/renderer.cpp
LINK=-lGL -lglfw -lGLEW -lSOIL -lpugixml
OPTIONS=-DGLEW_STATIC -Iheaders -g


all:
	$(CC) $(FILES) $(LINK) $(OPTIONS)