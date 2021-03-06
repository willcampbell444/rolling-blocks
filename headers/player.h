#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include <iostream>
#include <globals.h>
#include <heightMap.h>
#include <math.h>
#include <vector>
#include <renderer.h>

class Player {
public:
    Player(Renderer* renderer);
    void create(int x, int y, unsigned char* map, std::vector<glm::vec3> startPosition);
    void draw(glm::mat4 viewProjectionMatrix);
    void move(int x, int z, unsigned char* map);
    void changeGroup(int direction);
    void update(unsigned char* map, GLfloat deltaTime);
    bool win();
    bool getWinStatus();
    int getMoveCount();
    glm::vec3 getCameraPos();
    glm::vec2 getCameraDistance();
    void restart();
    void end();
private:
    void setMinMax();
    void gravity();
    void onBlock(int x, int z);
    void onWinTile(unsigned char* map);
    void checkVictory(unsigned char* map);
    void fillHeightMap();
    void sever();
    void attach();

    int _floorWidth, _floorLength;
    bool _isBeginning = true;
    bool _isEnding = false;
    bool _wait = false;
    bool _isTransition = false;
    bool _isCameraTransition = false;
    bool _isRestartTransition = false;
    bool _finished = false;
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
    float _timeSinceTransition = 0;
    int _endTimer = 0;
    int _angleSign = 1;
    int _minX, _maxX;
    int _minY, _maxY;
    int _minZ, _maxZ;
    int _group = 0;
    std::vector<glm::vec3> _playerPeices;
    std::vector<glm::vec3> _oldPeices;
    std::vector<glm::vec3> _newPeices;
    std::vector<glm::vec3> _static;
    std::vector<glm::vec4> _done;
    std::vector<glm::vec4> _falling;
    std::vector<int> playerGroups;
    std::vector<int> staticGroups;
    std::vector<int> _groups;
    std::vector<glm::vec3> _startPosition;
    HeightMap _heightMap;
    glm::mat4 _transformMatrix;

    int _moveCount = 0;

    Renderer* _renderer;

    GLuint _vertexArrayObject;
    GLuint _doneVertexArrayObject;
    GLuint _lineVertexArrayObject;
    GLuint _staticLineVertexArrayObject;
};

#endif