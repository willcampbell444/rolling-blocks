#ifndef FLOOR_H
#define FLOOR_H

#include <GL/glew.h>
#include <shaders.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

class Floor {
public:
    Floor(Shaders* shader, int width, int length);
    ~Floor();
    void create();
    void draw(glm::mat4 viewProjectionMatrix);
private:
    int _width, _length;

    GLuint _vertexArrayObject;
    GLuint _vertexBufferObject;
    GLuint _elementBufferObject;

    GLuint _lineVertexArrayObject;
    GLuint _lineElementBufferObject;
    GLuint _lineVertexBufferObject;

    Shaders* _shader;
};

#endif