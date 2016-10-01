#ifndef MAP_H
#define MAP_H

#include <fstream>
#include <vector>
#include <glm/glm.hpp>

class Map {
public:
	~Map();
	void read(const char* filename);
	unsigned char* getTiles();
	int getWidth();
	int getLength();
	std::vector<glm::vec3> getStartPosition();
	std::vector<glm::vec2> getVictoryTiles();
private:
	unsigned char* _tiles = nullptr;
	int _width;
	int _length;
	std::vector<glm::vec3> _startPosition;
	std::vector<glm::vec2> _victoryTiles;
};

#endif