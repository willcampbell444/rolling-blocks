#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

class HeightMapRow {
public:
	~HeightMapRow();
	void create(int w);
	int operator[](int i) const;
	int& operator[](int i);
private:
	int* _heightMapRow = nullptr;
	int _width;
	int _zero = 0;
};


class HeightMap {
public:
	~HeightMap();
	void create(int w, int l);
	HeightMapRow operator[](int i) const;
	HeightMapRow& operator[](int i);
private:
	HeightMapRow* _heightMap = nullptr;
	HeightMapRow _zero;
	int _length;
};

#endif