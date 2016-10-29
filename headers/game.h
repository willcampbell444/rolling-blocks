#ifndef GAME_H
#define GAME_H

// #define PUGIXML_WCHAR_MODE UTF-8

#include <shaders.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
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

    GLFWwindow* _window;

    int _level = 0;
    std::vector<const char*> _levelFileNames;
    std::vector<const char*> _levelNames;
    bool _end = false;

    Renderer* _renderer;

    glm::mat4 _viewMatrix;
    glm::mat4 _projectionMatrix;
    glm::mat4 _projectionViewMatrix;

    glm::vec3 _cameraPos;

    pugi::xml_node _currentLayer;
    pugi::xml_document _document;

    int _state;

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