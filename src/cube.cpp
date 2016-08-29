#include <cube.h>


Cube::Cube(float x, float y, float z, float w, float h, float d, int offset): _offset(offset) {
	_vertices = new float[8*_offset];
	_w = w/2.0f;
	_h = h/2.0f;
	_d = d/2.0f;
	this->move(x, y, z);
}

Cube::~Cube() {
	delete _vertices;
}

int Cube::size() {
	return _offset*8;
}

void Cube::move(float x, float y, float z) {
	_x = x;
	_y = y;
	_z = z;
	_vertices[    0    ] = _x - _w;
	_vertices[ _offset ] = _x - _w;
	_vertices[_offset*2] = _x + _w;
	_vertices[_offset*3] = _x + _w;
	_vertices[_offset*4] = _x - _w;
	_vertices[_offset*5] = _x - _w;
	_vertices[_offset*6] = _x + _w;
	_vertices[_offset*7] = _x + _w;

	for (int i = 0; i < 4; i++) {
		_vertices[  i   * _offset+1] = _y - _h;
		_vertices[(4+i) * _offset+1] = _y + _h;
	}

	_vertices[2 +     0    ] = _z + _d;
	_vertices[2 +  _offset ] = _z - _d;
	_vertices[2 + _offset*2] = _z - _d;
	_vertices[2 + _offset*3] = _z + _d;
	_vertices[2 + _offset*4] = _z + _d;
	_vertices[2 + _offset*5] = _z - _d;
	_vertices[2 + _offset*6] = _z - _d;
	_vertices[2 + _offset*7] = _z + _d;
}

void Cube::moveBy(float x, float y, float z) {
	this->move(_x+x, _y+y, _z+z);
}

void Cube::setColor(float r, float g, float b) {
	for (int i = 0; i < 8; i++) {
		_vertices[i*_offset+3] = r;
		_vertices[i*_offset+4] = g;
		_vertices[i*_offset+5] = b;
	}
}

float* Cube::getArray() {
	return _vertices;
}

float* _vertices;
float _x, _y, _z;
float _w, _h, _d;
float _offset;
