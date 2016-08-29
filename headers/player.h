#ifndef PLAYER_H
#define PLAYER_H

#include <GL/glew.h>
#include <shaders.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <shaders.h>
#include <cmath>
#include <iostream>

class Player {
public:
    Player(Shaders* shader, int x, int y);
    ~Player();
    void draw(glm::mat4 viewProjectionMatrix);
    void move(int x, int z);
    void update();
    void setMinMax();
    glm::vec3 getCameraPos();
private:
    int _floorWidth, _floorLength;
    int _x = 4;
    int _z = 4;
    int _nextX = 0;
    int _nextZ = 0;
    bool _isTransition = false;
    glm::vec3 _direction;
    glm::vec3 _nextDirection;
    glm::vec3 _rotationAxis;
    glm::vec3 _rotationAxisPosition;
    glm::vec3 _oldCameraPos;
    glm::vec3 _newCameraPos;
    glm::vec3 _cameraPos;
    float _angle = 0.0f;
    int _frame = 0;
    int _angleSign = 1;
    int _minX, _minX;
    int _minY, _minY;
    int _minZ, _minZ;
    std::vector<glm::vec3> _playerPeices;
    std::vector<glm::vec3> _nextPeices;
    glm::mat4 _transformMatrix;

    Shaders* _shader;

    GLuint _vertexArrayObject;
    GLuint _vertexBufferObject;
    GLuint _elementBufferObject;

    GLuint _lineVertexArrayObject;
    GLuint _lineVertexBufferObject;
    GLuint _lineElementBufferObject;
};

#endif