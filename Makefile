CC=g++
FILES=src/main.cpp src/shaders.cpp src/game.cpp src/floor.cpp src/player.cpp src/map.cpp src/heightMap.cpp src/menu.cpp src/renderer.cpp
LINK=-lopengl32 -lglfw3 -lglew32 -lpugixml
OPTIONS=-DGLEW_STATIC -Iheaders -IC:\C++\include -LC:\C++\lib -std=c++11 -mwindows -static-libgcc -static-libstdc++

all: shaders.o map.o heightMap.o renderer.o floor.o player.o menu.o game.o main.o
	$(CC) shaders.o map.o heightMap.o renderer.o floor.o player.o menu.o game.o main.o $(OPTIONS) -lopengl32 -lglfw3 -lglew32 -lpugixml -o play

lvledit: shaders.o map.o renderer.o levelEdit.o lvledit.o
	$(CC) shaders.o map.o renderer.o lvledit.o levelEdit.o $(OPTIONS) -lopengl32 -lglfw3 -lglew32 -static-libgcc -static-libstdc++ -o lvledit

lvledit.o: src/lvledit.cpp headers/levelEdit.h
	$(CC) -c src/lvledit.cpp $(OPTIONS)

levelEdit.o: src/levelEdit.cpp headers/levelEdit.h headers/globals.h headers/renderer.h headers/shaders.h headers/map.h
	$(CC) -c src/levelEdit.cpp $(OPTIONS)

shaders.o: src/shaders.cpp headers/shaders.h
	$(CC) -c src/shaders.cpp $(OPTIONS)

map.o: src/map.cpp headers/map.h
	$(CC) -c src/map.cpp $(OPTIONS)

heightMap.o: src/heightMap.cpp headers/heightMap.h
	$(CC) -c src/heightMap.cpp $(OPTIONS)

renderer.o: src/renderer.cpp headers/renderer.h headers/globals.h
	$(CC) -c src/renderer.cpp $(OPTIONS)

floor.o: src/floor.cpp headers/floor.h headers/globals.h headers/renderer.h
	$(CC) -c src/floor.cpp $(OPTIONS)

player.o: src/player.cpp headers/player.h headers/globals.h headers/renderer.h headers/heightMap.h
	$(CC) -c src/player.cpp $(OPTIONS)

menu.o: src/menu.cpp headers/menu.h headers/globals.h headers/renderer.h
	$(CC) -c src/menu.cpp $(OPTIONS)

game.o: src/game.cpp headers/game.h headers/floor.h headers/player.h headers/globals.h headers/map.h headers/menu.h headers/renderer.h
	$(CC) -c src/game.cpp $(OPTIONS)

main.o: src/main.cpp headers/game.h
	$(CC) -c src/main.cpp $(OPTIONS)

clean:
	rm *o play lvledit