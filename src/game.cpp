#include <game.h>

Game::Game() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_SAMPLES, 8);

    _window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr);

    glfwMakeContextCurrent(_window);

    glewExperimental = GL_TRUE;
    glewInit();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);

    // glEnable (GL_BLEND);
    // glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // glEnable(GL_POLYGON_STIPPLE);

    if (!_shaders[0].loadShader(GL_VERTEX_SHADER, "shaders/vertex.glsl")) {
        std::cout << "Vertex Shader Failed To Compile" << std::endl;
    }
    if (!_shaders[0].loadShader(GL_FRAGMENT_SHADER, "shaders/fragment.glsl")) {
        std::cout << "Fragment Shader Failed To Compile" << std::endl;
    }
    _shaders[0].createProgram();

    _shaders[0].use();

    _projectionMatrix = glm::perspective(glm::radians(50.0f), 800.0f / 600.0f, 1.0f, 50.0f);

    glClearColor(GLOBAL::BACKGROUND.r, GLOBAL::BACKGROUND.g, GLOBAL::BACKGROUND.b, 1.0f);

    _renderer = new Renderer(&_shaders[0]);
    _floor = new Floor(_renderer);
    _player = new Player(_renderer);
    _menu = new Menu(&_shaders[0]);

    _state = GLOBAL::STATE_MENU;

    if (!_document.load_file("maps/gameOrder.xml")) {
        std::cout << "Game order failed to load!" << std::endl;
    }
    _currentLayer = _document.first_child();

    for (pugi::xml_node i: _currentLayer.children()) {
        _levelNames.push_back(i.attribute("name").value());
    }

    _menu->setOptions(_levelNames, 1);
}

Game::~Game() {
    glDeleteBuffers(2, _vbo);
    glDeleteBuffers(1, _ebo);
    glDeleteVertexArrays(2, _vao);

    delete _floor;
    delete _player;

    glfwTerminate();
}

void Game::selectOption(int optionNum) {
    if (optionNum == -2) {
        _menu->setOptions(_levelNames, -1);
    } else {
        int count = 0;
        pugi::xml_node child = _currentLayer.first_child();
        while (count < optionNum) {
            count += 1;
            child = child.next_sibling();
        }
        if (strcmp(child.name(), "level") == 0) {
            loadMap(child.attribute("fileName").value());
            _state = GLOBAL::STATE_PLAY;
        } else if (strcmp(child.name(), "option") == 0) {
            _levelNames.clear();
            _currentLayer = child;
            for (pugi::xml_node i: _currentLayer.children()) {
                _levelNames.push_back(i.attribute("name").value());
            }
            _menu->setOptions(_levelNames, 1);
        }
    }
}

void Game::previousOption() {
    if (_currentLayer != _document.child("option")) {
        _currentLayer = _currentLayer.parent();

        _levelNames.clear();

        for (pugi::xml_node i: _currentLayer.children()) {
            _levelNames.push_back(i.attribute("name").value());
        }

        _menu->end();
    }
}

GLFWwindow* Game::getWindow() {
    return _window;
}

bool Game::end() {
    return _end;
}

void Game::loadMap(const char* fileName) {
    _map.read(fileName);
    _level += 1;

    _floor->create(_map.getWidth(), _map.getLength(), _map.getTiles());
    _player->create(_map.getWidth(), _map.getLength(), _map.getTiles(), _map.getStartPosition());

    _cameraAngle = 0.0f;
    _cameraHeight = 0.0f;
}

void Game::update() {
    glfwPollEvents();

    if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(_window, GL_TRUE);
    }

    glm::vec3 cameraPos;
    glm::vec2 cameraDistance;

    if (_state == GLOBAL::STATE_PLAY) {
        if (_cameraAngle > 315 || _cameraAngle < 45) {
            if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS) {
                _player->move(1, 0, _map.getTiles());
            }
            if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS) {
                _player->move(0, -1, _map.getTiles());
            }
            if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS) {
                _player->move(-1, 0, _map.getTiles());
            }
            if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS) {
                _player->move(0, 1, _map.getTiles());
            }
        } else if (_cameraAngle > 45 && _cameraAngle < 135) {
            if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS) {
                _player->move(0, 1, _map.getTiles());
            }
            if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS) {
                _player->move(1, 0, _map.getTiles());
            }
            if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS) {
                _player->move(0, -1, _map.getTiles());
            }
            if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS) {
                _player->move(-1, 0, _map.getTiles());
            }
        } else if (_cameraAngle > 135 && _cameraAngle < 225) {
            if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS) {
                _player->move(-1, 0, _map.getTiles());
            }
            if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS) {
                _player->move(0, 1, _map.getTiles());
            }
            if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS) {
                _player->move(1, 0, _map.getTiles());
            }
            if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS) {
                _player->move(0, -1, _map.getTiles());
            }
        } else {
            if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS) {
                _player->move(0, -1, _map.getTiles());
            }
            if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS) {
                _player->move(-1, 0, _map.getTiles());
            }
            if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS) {
                _player->move(0, 1, _map.getTiles());
            }
            if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS) {
                _player->move(1, 0, _map.getTiles());
            }
        }

        _player->update(_map.getTiles(), _map.getVictoryTiles());

        cameraPos = _player->getCameraPos();
        cameraDistance = _player->getCameraDistance();
    
        if (_player->win()) {
            _menu->setOptions(_levelNames, 1);
            _state = GLOBAL::STATE_MENU;
        }
    } else if (_state == GLOBAL::STATE_MENU) {
        cameraPos = _menu->getCameraPos();
        cameraDistance = _menu->getCameraDistance();

        if (
            glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS
            || glfwGetKey(_window, GLFW_KEY_Z) == GLFW_PRESS
        ) {
            _menu->move(-1);
        } else if (
            glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS
            || glfwGetKey(_window, GLFW_KEY_X) == GLFW_PRESS
        ) {
            _menu->move(1);
        }

        if (glfwGetKey(_window, GLFW_KEY_W)) {
            _menu->select();
        }

        if (glfwGetKey(_window, GLFW_KEY_F) && _menu->isStill()) {
            previousOption();
        }

        _menu->update();
        if (_menu->result() != -1) {
            selectOption(_menu->result());
        }
    }

    if (glfwGetKey(_window, GLFW_KEY_Q) == GLFW_PRESS || glfwGetKey(_window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        _cameraAngle += 1.0f;
    }
    if (glfwGetKey(_window, GLFW_KEY_E) == GLFW_PRESS || glfwGetKey(_window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        _cameraAngle -= 1.0f;
    }
    if (glfwGetKey(_window, GLFW_KEY_UP) == GLFW_PRESS) {
        _cameraHeight += 0.1f;
    }
    if (glfwGetKey(_window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        _cameraHeight -= 0.1f;
    }

    if (glfwGetKey(_window, GLFW_KEY_Z) == GLFW_PRESS) {
        _player->changeGroup(-1);
    }
    if (glfwGetKey(_window, GLFW_KEY_X) == GLFW_PRESS) {
        _player->changeGroup(1);
    }

    if (_cameraAngle > 360) {
        _cameraAngle = 0;
    } else if (_cameraAngle < 0) {
        _cameraAngle = 360;
    }

    _cameraPos = glm::vec3(
        cameraPos.x - std::cos(_cameraAngle*(3.14159/180))*cameraDistance.x,
        cameraPos.y + cameraDistance.y + _cameraHeight,
        cameraPos.z - std::sin(_cameraAngle*(3.14159/180))*cameraDistance.x
    );

    _viewMatrix = glm::lookAt(
        _cameraPos,
        cameraPos,
        glm::vec3(0.0f, 1.0f, 0.0f)
    );

    _projectionViewMatrix = _projectionMatrix * _viewMatrix;
}

void Game::draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _shaders[0].use();

    glUniform3f(
        _shaders[0].getUniformLocation("cameraPosition"), 
        _cameraPos.x,
        _cameraPos.y,
        _cameraPos.z
    );

    if (_state == GLOBAL::STATE_PLAY) {
        _floor->draw(_projectionViewMatrix);
        _player->draw(_projectionViewMatrix);
    } else if (_state == GLOBAL::STATE_MENU) {
        _menu->draw(_projectionViewMatrix);
    }

    glfwSwapBuffers(_window);
}