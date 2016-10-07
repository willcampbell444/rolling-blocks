#include <heightMap.h>
#include <iostream>

HeightMap::~HeightMap() {
	delete[] _heightMap;
}

void HeightMap::create(int l, int w) {
	_length = l;
	_zero.create(0);

    _heightMap = new HeightMapRow[l];
    for (int i = 0; i < l; i++) {
        _heightMap[i].create(w);
    }
}

HeightMapRow HeightMap::operator[](int i) const {
	if (i >= 0 && i < _length) {
		return _heightMap[i];
	}
	return _zero;
}

HeightMapRow& HeightMap::operator[](int i) {
	if (i >= 0 && i < _length) {
		return _heightMap[i];
	}
	return _zero;
}

HeightMapRow::~HeightMapRow() {
	delete[] _heightMapRow;
}

void HeightMapRow::create(int w) {
	_width = w;

	_heightMapRow = new int[_width];
	for (int i = 0; i < _width; i++) {
		_heightMapRow[i] = 0;
	}
}

int HeightMapRow::operator[](int i) const {
	if (i >= 0 && i < _width) {
		return _heightMapRow[i];
	}
	return 0;
}

int& HeightMapRow::operator[](int i) {
	if (i >= 0 && i < _width) {
		return _heightMapRow[i];
	}
	return _zero;
}
