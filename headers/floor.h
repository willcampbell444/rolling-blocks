#ifndef FLOOR_H
#define FLOOR_H

#include <GL/glew.h>
#include <shaders.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <globals.h>
#include <renderer.h>

class Floor {
public:
    Floor(Renderer* renderer);
    void create(int width, int length, unsigned char* tiles);
    void draw(glm::mat4 viewProjectionMatrix);
    unsigned char* getMap();
private:
    int _width, _length, _numFilled;

    unsigned char* _map;

    Renderer* _renderer;
};

#endif