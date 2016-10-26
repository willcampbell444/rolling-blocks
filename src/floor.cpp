#include <floor.h>

Floor::Floor(Renderer* renderer) {
    _renderer = renderer;
}

void Floor::create(int width, int length, unsigned char* tiles) {
    _width = width;
    _length = length;

    _map = tiles;
}

unsigned char* Floor::getMap() {
    return _map;
}

void Floor::draw(glm::mat4 viewProjectionMatrix) {
    for (int x = 0; x < _width; x += 1) {
        for (int z = 0; z < _length; z += 1) {
            if (_map[x*_length + z] == 1) {
                _renderer->drawFloorTile(viewProjectionMatrix, x, z);
            } else if (_map[x*_length + z] == 2) {
                _renderer->drawVictoryTile(viewProjectionMatrix, x, z);
            }
        }
    }
}