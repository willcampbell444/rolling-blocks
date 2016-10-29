CC=g++ -g

all: shaders.o map.o heightMap.o renderer.o floor.o player.o menu.o game.o main.o
	$(CC) shaders.o map.o heightMap.o renderer.o floor.o player.o menu.o game.o main.o -lGL -lglfw -lGLEW -lpugixml -DGLEW_STATIC -Iheaders -o play

lvledit: shaders.o map.o renderer.o levelEdit.o lvledit.o
	$(CC) shaders.o map.o renderer.o lvledit.o levelEdit.o -lGL -lglfw -lGLEW -DGLEW_STATIC -Iheaders -o lvledit

lvledit.o: src/lvledit.cpp headers/levelEdit.h
	$(CC) -c src/lvledit.cpp -Iheaders

levelEdit.o: src/levelEdit.cpp headers/levelEdit.h headers/globals.h headers/renderer.h headers/shaders.h headers/map.h
	$(CC) -c src/levelEdit.cpp -Iheaders

shaders.o: src/shaders.cpp headers/shaders.h
	$(CC) -c src/shaders.cpp -Iheaders

map.o: src/map.cpp headers/map.h
	$(CC) -c src/map.cpp -Iheaders

heightMap.o: src/heightMap.cpp headers/heightMap.h
	$(CC) -c src/heightMap.cpp -Iheaders

renderer.o: src/renderer.cpp headers/renderer.h headers/globals.h
	$(CC) -c src/renderer.cpp -Iheaders

floor.o: src/floor.cpp headers/floor.h headers/globals.h headers/renderer.h
	$(CC) -c src/floor.cpp -Iheaders

player.o: src/player.cpp headers/player.h headers/globals.h headers/renderer.h headers/heightMap.h
	$(CC) -c src/player.cpp -Iheaders

menu.o: src/menu.cpp headers/menu.h headers/globals.h headers/renderer.h
	$(CC) -c src/menu.cpp -Iheaders

game.o: src/game.cpp headers/game.h headers/floor.h headers/player.h headers/globals.h headers/map.h headers/menu.h headers/renderer.h
	$(CC) -c src/game.cpp -Iheaders

main.o: src/main.cpp headers/game.h
	$(CC) -c src/main.cpp -Iheaders

clean:
	rm *o play lvledit