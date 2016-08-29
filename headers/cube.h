#ifndef CUBE_H
#define CUBE_H

class Cube {
public:
	Cube(float x, float y, float z, float w, float h, float d, int offset);
	~Cube();
	void move(float x, float y, float z);
	void moveBy(float x, float y, float z);
	void setColor(float r, float g, float b);
	float* getArray();
	inline float x() {return _x;};
	inline float y() {return _y;};
	inline float z() {return _z;};
	int size();
private:
	float* _vertices;
	float _x, _y, _z;
	float _w, _h, _d;
	int _offset;
};

#endif