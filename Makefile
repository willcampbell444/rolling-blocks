CC=g++
FILES=src/main.cpp src/shaders.cpp src/game.cpp src/floor.cpp src/player.cpp src/map.cpp src/heightMap.cpp src/menu.cpp src/renderer.cpp
LINK=-lopengl32 -lglfw3 -lglew32 -lpugixml
OPTIONS=-DGLEW_STATIC -Iheaders -IC:\C++\include -LC:\C++\lib -std=c++11


all:
	$(CC) $(FILES) $(LINK) $(OPTIONS)