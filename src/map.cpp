#include <map.h>
#include <iostream>

Map::~Map() {
	delete _tiles;
}

void Map::read(const char* filename) {
	std::ifstream file;
	file.open(filename);

	file >> _width;
	file >> _length;

	if (_tiles) {
		delete[] _tiles;
	}
	_victoryTiles.clear();

	_tiles = new unsigned char[_width*_length];
	for (int i = 0; i < _width*_length; i++) {
		file >> _tiles[i];
		_tiles[i] -= '0';
		if (_tiles[i] == 2) {
			_victoryTiles.push_back(glm::vec2(i/_width, i%_width));
		}
	}

	_startPosition.clear();

	int playerBlockCount;
	int x, y, z;
	file >> playerBlockCount;
	for (int i = 0; i < playerBlockCount; i++) {
		file >> x;
		file >> y;
		file >> z;
		_startPosition.push_back(glm::vec3(x, y, z));
	}
}

unsigned char* Map::getTiles() {
	return _tiles;
}

int Map::getWidth() {
	return _width;
}

int Map::getLength() {
	return _length;
}

std::vector<glm::vec3> Map::getStartPosition() {
	return _startPosition;
}


std::vector<glm::vec2> Map::getVictoryTiles() {
	return _victoryTiles;
}