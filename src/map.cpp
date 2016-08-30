#include <map.h>

Map::~Map() {
	delete _tiles;
}

void Map::read(const char* filename) {
	std::ifstream file;
	file.open(filename);

	file >> _width;
	file >> _length;

	_tiles = new unsigned char[_width*_length];
	for (int i = 0; i < _width*_length; i++) {
		file >> _tiles[i];
		_tiles[i] -= '0';
	}

	unsigned char playerBlockCount, x, y, z;
	file >> playerBlockCount;
	for (int i = 0; i < (playerBlockCount - '0'); i++) {
		file >> x;
		file >> y;
		file >> z;
		_startPosition.push_back(glm::vec3(x-'0', y-'0', z-'0'));
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