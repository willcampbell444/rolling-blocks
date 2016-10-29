#ifndef GAME_H
#define GAME_H

// #define PUGIXML_WCHAR_MODE UTF-8

#include <shaders.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <SOIL/SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <floor.h>
#include <player.h>
#include <cmath>
#include <map.h>
#include <vector>
#include <globals.h>
#include <pugixml.hpp>
#include <menu.h>
#include <renderer.h>
#include <cstring>

class Game {
public:
    Game();
    ~Game();
    void update();
    void draw();
    void loadMap(const char* fileName);
    bool end();
    GLFWwindow* getWindow();
private:
    void selectOption(int optionNum);
    void previousOption();

    GLfloat _vertices[56] = {
        //side
        -100, -0.01, -100, 1, 1, 1, 0.5,
        -100, -0.01,  100, 1, 1, 1, 0.5,
         100, -0.01,  100, 1, 1, 1, 0.5,
         100, -0.01, -100,  1, 1, 1, 0.5,

        -100, -10, -100, 1, 1, 1, 1,
        -100, -10,  100, 1, 1, 1, 1,
         100, -10,  100, 1, 1, 1, 1,
         100, -10, -100, 1, 1, 1, 1,
    };

    GLfloat _verticesTwo[24] = {
        //side
        -0.5, -0.5,  0, 1, 0, 0,
        -0.5,  0.5,  0, 0, 1, 0,
         0.5,  0.5,  0, 0, 0, 1,
         0.5, -0.5,  0, 1, 0, 0
    };

    GLuint _elements[36] = {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4,
        4, 5, 1, 1, 0, 4,
        6, 7, 3, 3, 2, 6,
        4, 0, 3, 3, 7, 4,
        5, 1, 2, 2, 6, 5
    };

    GLuint _elementsTwo[3] = {
        1, 2, 3
    };

    GLFWwindow* _window;
    Shaders _shaders[2];

    int _level = 0;
    std::vector<const char*> _levelFileNames;
    std::vector<const char*> _levelNames;
    bool _end = false;

    GLuint _vao[2];
    GLuint _vbo[2];
    GLuint _ebo[2];

    Renderer* _renderer;

    glm::mat4 _viewMatrix;
    glm::mat4 _projectionMatrix;
    glm::mat4 _projectionViewMatrix;

    glm::vec3 _cameraPos;

    pugi::xml_node _currentLayer;
    pugi::xml_document _document;

    int _state;

    glm::vec3 _gray;
    glm::vec3 _blue;

    Floor* _floor;
    Player* _player;
    Menu* _menu;

    Map _map;

    float _cameraAngle = 0.0f;
    float _cameraHeight = 0.0f;

    GLfloat _lastFrameTime;
    GLfloat _deltaTime;
};

#endif