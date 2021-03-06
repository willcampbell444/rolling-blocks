CC=g++
INCLUDE=-Iheaders -I/usr/include/freetype2 -I/usr/include/SDL2

all: shaders.o map.o heightMap.o pause.o fileLoader.o renderer.o floor.o player.o menu.o game.o main.o
	$(CC) shaders.o pause.o map.o fileLoader.o heightMap.o renderer.o floor.o player.o menu.o game.o main.o -lGL -lfreetype -lSDL2 -lGLEW -lpugixml -DGLEW_STATIC $(INCLUDE) -o play

lvledit: shaders.o map.o renderer.o levelEdit.o lvledit.o
	$(CC) shaders.o map.o renderer.o lvledit.o levelEdit.o -lGL -lglfw -lGLEW -lfreetype -DGLEW_STATIC $(INCLUDE) -o lvledit

fileLoader.o: src/fileLoader.cpp headers/fileLoader.h
	$(CC) -c src/fileLoader.cpp $(INCLUDE)

lvledit.o: src/lvledit.cpp headers/levelEdit.h
	$(CC) -c src/lvledit.cpp $(INCLUDE)

levelEdit.o: src/levelEdit.cpp headers/levelEdit.h headers/globals.h headers/renderer.h headers/shaders.h headers/map.h
	$(CC) -c src/levelEdit.cpp $(INCLUDE)

shaders.o: src/shaders.cpp headers/shaders.h
	$(CC) -c src/shaders.cpp $(INCLUDE)

pause.o: src/pause.cpp headers/pause.h headers/globals.h headers/renderer.h
	$(CC) -c src/pause.cpp $(INCLUDE)

map.o: src/map.cpp headers/map.h headers/fileLoader.h
	$(CC) -c src/map.cpp $(INCLUDE)

heightMap.o: src/heightMap.cpp headers/heightMap.h
	$(CC) -c src/heightMap.cpp $(INCLUDE)

renderer.o: src/renderer.cpp headers/renderer.h headers/globals.h
	$(CC) -c src/renderer.cpp $(INCLUDE)

floor.o: src/floor.cpp headers/floor.h headers/globals.h headers/renderer.h
	$(CC) -c src/floor.cpp $(INCLUDE)

player.o: src/player.cpp headers/player.h headers/globals.h headers/renderer.h headers/heightMap.h
	$(CC) -c src/player.cpp $(INCLUDE)

menu.o: src/menu.cpp headers/menu.h headers/globals.h headers/renderer.h
	$(CC) -c src/menu.cpp $(INCLUDE)

game.o: src/game.cpp headers/game.h headers/fileLoader.h headers/floor.h headers/player.h headers/globals.h headers/map.h headers/menu.h headers/renderer.h
	$(CC) -c src/game.cpp $(INCLUDE)

main.o: src/main.cpp headers/game.h
	$(CC) -c src/main.cpp $(INCLUDE)

clean:
	rm *o play lvledit