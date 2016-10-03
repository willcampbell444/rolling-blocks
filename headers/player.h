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
#include <globals.h>
// #include <algorithm>
#include <math.h>
#include <vector>

class Player {
public:
    Player(Shaders* shader);
    void create(int x, int y, unsigned char* map, std::vector<glm::vec3> startPosition);
    void draw(glm::mat4 viewProjectionMatrix);
    void move(int x, int z, unsigned char* map);
    void update(unsigned char* map, std::vector<glm::vec2> victoryTiles);
    bool win();
    glm::vec3 getCameraPos();
    glm::vec2 getCameraDistance();
private:
    void setMinMax();
    void gravity();
    void onBlock(int x, int z);
    void onWinTile(unsigned char* map);
    void checkVictory(std::vector<glm::vec2> victoryTiles);
    void fillHeightMap();
    void sever();
    void attach();

    int _floorWidth, _floorLength;
    bool _isTransition = false;
    bool _isCameraTransition = false;
    bool _won = false;
    glm::vec3 _rotationAxis;
    glm::vec3 _rotationAxisPosition;
    glm::vec3 _oldCameraPos;
    glm::vec3 _newCameraPos;
    glm::vec3 _cameraPos;
    glm::vec2 _cameraDistance;
    glm::vec2 _oldCameraDistance;
    glm::vec2 _newCameraDistance;
    float _angle = 0.0f;
    int _frame = 0;
    int _endTimer = 0;
    int _angleSign = 1;
    int _minX, _maxX;
    int _minY, _maxY;
    int _minZ, _maxZ;
    std::vector<glm::vec3> _playerPeices;
    std::vector<glm::vec3> _oldPeices;
    std::vector<glm::vec3> _newPeices;
    std::vector<glm::vec3> _static;
    std::vector<glm::vec3> _done;
    std::vector<glm::vec4> _falling;
    int** _heightMap = nullptr;
    glm::mat4 _transformMatrix;

    Shaders* _shader;

    GLuint _vertexArrayObject;
    GLuint _doneVertexArrayObject;
    GLuint _lineVertexArrayObject;
};

#endif