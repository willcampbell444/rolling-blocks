#ifndef FLOOR_H
#define FLOOR_H

#include <GL/glew.h>
#include <shaders.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <globals.h>

class Floor {
public:
    Floor(Shaders* shader);
    ~Floor();
    void create(int width, int length, unsigned char* tiles);
    void draw(glm::mat4 viewProjectionMatrix);
    unsigned char* getMap();
private:
    int _width, _length, _numFilled;

    unsigned char* _map;

    GLuint _vertexArrayObject;
    GLuint _vertexBufferObject;
    GLuint _elementBufferObject;

    GLuint _lineVertexArrayObject;
    GLuint _lineElementBufferObject;
    GLuint _lineVertexBufferObject;

    Shaders* _shader;
};

#endif