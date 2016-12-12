#ifndef GAME_H
#define GAME_H

#include <shaders.h>
#include <GL/glew.h>
#include <SDL.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <floor.h>
#include <player.h>
#include <cmath>
#include <map.h>
#include <vector>
#include <globals.h>
#include <pugixml.hpp>
#include <menu.h>
#include <renderer.h>
#include <pause.h>
#include <cstring>
#include <sstream>
#include <fileLoader.h>
#include <string>

class Game {
public:
    Game();
    ~Game();
    void update();
    void draw();
    void loadMap(const char* fileName);
    bool end();
    SDL_Window* getWindow();
private:
    void selectOption(int optionNum);
    void writeSave();
    void loadSave();
    void resize();
    void previousOption();
    void setLevelNames(pugi::xml_node parent);
    bool isWon(pugi::xml_node node);
    int moveCount(pugi::xml_node node);

    SDL_Window* _window;
    SDL_GLContext _context;
    SDL_Event* _event;

    std::vector<int> _itemsSelected;

    std::vector<const char*> _levelFileNames;
    std::vector<int> _moveCounts;
    std::vector<MenuOption> _levelNames;
    std::vector<std::string> _beatLevels;
    bool _end = false;

    Renderer* _renderer;

    glm::mat4 _viewMatrix;
    glm::mat4 _projectionMatrix;
    glm::mat4 _projectionViewMatrix;

    glm::vec3 _cameraPos;

    pugi::xml_node _currentLayer;
    pugi::xml_document _document;

    double _lastFPSTime;
    int _numFrames = 0;

    int _state;

    std::string _levelFileName;

    Floor* _floor;
    Player* _player;
    Menu* _menu;
    Pause _pause;

    Map _map;

    bool _pauseTransition = false;
    bool _unpauseTransition = false;
    GLfloat _transitionTime = 0;
    GLfloat _dimAmount;
    GLfloat _pauseTextHeight;
    GLfloat _gameTextHeight;

    float _cameraAngle = 0.0f;
    float _cameraHeight = 0.0f;

    int _FPS;

    GLfloat _lastFrameTime;
    GLfloat _deltaTime;

    bool _keys[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    int _screenWidth, _screenHeight;
    glm::vec2 _mousePos;
    bool _click;

    bool _showControls = true;
};

#endif