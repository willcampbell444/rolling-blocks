#include <game.h>

Game::Game() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 8);

    _window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr);

    glfwMakeContextCurrent(_window);

    glewExperimental = GL_TRUE;
    glewInit();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_CULL_FACE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 

    _screenWidth = 800;
    _screenHeight = 600;

    _projectionMatrix = glm::perspective(glm::radians(50.0f), 800.0f / 600.0f, 1.0f, 1000.0f);

    glClearColor(GLOBAL::BACKGROUND.r, GLOBAL::BACKGROUND.g, GLOBAL::BACKGROUND.b, 1.0f);

    _renderer = new Renderer();
    _floor = new Floor(_renderer);
    _player = new Player(_renderer);
    _menu = new Menu(_renderer);

    _state = GLOBAL::STATE_MENU;

    if (!_document.load_file("maps/gameOrder.xml")) {
        std::cout << "Game order failed to load!" << std::endl;
    }
    _currentLayer = _document.first_child();

    loadSave();

    setLevelNames(_currentLayer);

    _menu->setOptions(_levelNames, 1, 0);

    _lastFrameTime = glfwGetTime();
    _lastFPSTime = glfwGetTime();
    _numFrames = 0;
}

Game::~Game() {
    delete _floor;
    delete _player;

    glfwTerminate();
}

void Game::resize() {
    // float change = (_screenHeight/600.0f);
    _projectionMatrix = glm::perspective(glm::radians(50.0f), (float)_screenWidth/_screenHeight, 1.0f, 1000.0f);
    glViewport(0, 0, _screenWidth, _screenHeight);
    _renderer->resize(_screenWidth, _screenHeight);
}

void Game::selectOption(int optionNum) {
    if (optionNum == -2) {
        _menu->setOptions(_levelNames, -1, _itemsSelected.back());
        _itemsSelected.pop_back();
    } else {
        int count = 0;
        pugi::xml_node child = _currentLayer.first_child();
        while (count < optionNum) {
            count += 1;
            child = child.next_sibling();
        }
        if (strcmp(child.name(), "level") == 0) {
            loadMap(child.attribute("fileName").value());
            _levelFileName = child.attribute("fileName").value();
            _state = GLOBAL::STATE_PLAY;
        } else if (strcmp(child.name(), "option") == 0) {
            _currentLayer = child;
            setLevelNames(_currentLayer);
            _menu->setOptions(_levelNames, 1, 0);
        }
        _itemsSelected.push_back(optionNum);
    }
}

void Game::previousOption() {
    if (_currentLayer != _document.child("option")) {
        _currentLayer = _currentLayer.parent();

        setLevelNames(_currentLayer);

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

    _floor->create(_map.getWidth(), _map.getLength(), _map.getTiles());
    _player->create(_map.getWidth(), _map.getLength(), _map.getTiles(), _map.getStartPosition());

    _cameraAngle = 0.0f;
    _cameraHeight = 0.0f;
}

void Game::setLevelNames(pugi::xml_node parent) {
    _levelNames.clear();

    for (pugi::xml_node i: parent.children()) {
        _levelNames.push_back(MenuOption(i.attribute("name").value(), isWon(i), moveCount(i)));
    }
}

int Game::moveCount(pugi::xml_node node) {
    if (strcmp(node.name(), "option") == 0) {
        return -1;
    }
    bool beat = false;
    int count;
    for (count = 0; count < _beatLevels.size(); count++) {
        if (_beatLevels[count] == node.attribute("fileName").value()) {
            beat = true;
            break;
        }
    }
    if (beat) {
        return _moveCounts[count];
    }
    return -1;
}

bool Game::isWon(pugi::xml_node node) {
    if (strcmp(node.name(), "option") == 0) {
        bool allWon = true;
        for (pugi::xml_node i: node.children()) {
            if (!isWon(i)) {
                allWon = false;
            }
        }
        return allWon;
    } else {
        bool beat = false;
        for (auto j: _beatLevels) {
            if (j == node.attribute("fileName").value()) {
                beat = true;
                break;
            }
        }
        return beat;
    }
}

void Game::update() {
    glfwPollEvents();

    int w, h;
    glfwGetFramebufferSize(_window, &w, &h);
    if (w != _screenWidth || h != _screenHeight) {
        _screenWidth = w;
        _screenHeight = h;
        resize();
    }

    _deltaTime = glfwGetTime() - _lastFrameTime;
    _lastFrameTime = glfwGetTime();
    _numFrames += 1;

    if (_lastFPSTime < glfwGetTime()-1) {
        // Print Framerate:
        // std::cout << _numFrames << std::endl;
        _lastFPSTime = glfwGetTime();
        _numFrames = 0;
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

        if (glfwGetKey(_window, GLFW_KEY_R) == GLFW_PRESS) {
            _player->restart();
        }

        if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            _player->end();
        }

        _player->update(_map.getTiles(), _deltaTime);

        cameraPos = _player->getCameraPos();
        cameraDistance = _player->getCameraDistance();

        if (glfwGetKey(_window, GLFW_KEY_Q) == GLFW_PRESS || glfwGetKey(_window, GLFW_KEY_LEFT) == GLFW_PRESS) {
            _cameraAngle += 90.0f * _deltaTime;
        }
        if (glfwGetKey(_window, GLFW_KEY_E) == GLFW_PRESS || glfwGetKey(_window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
            _cameraAngle -= 90.0f * _deltaTime;
        }

        if (_cameraAngle > 360) {
            _cameraAngle = 0;
        } else if (_cameraAngle < 0) {
            _cameraAngle = 360;
        }

        if (glfwGetKey(_window, GLFW_KEY_Z) == GLFW_PRESS) {
            _player->changeGroup(-1);
        }
        if (glfwGetKey(_window, GLFW_KEY_X) == GLFW_PRESS) {
            _player->changeGroup(1);
        }
    
        if (_player->win()) {
            _cameraAngle = 0;
            if (_player->getWinStatus()) {
                bool isNew = true;
                int count = 0;
                for (auto level: _beatLevels) {
                    if (level == _levelFileName) {
                        isNew = false;
                        break;
                    }
                    count += 1;
                }
                if (isNew) {
                    _beatLevels.push_back(_levelFileName);
                    _moveCounts.push_back(_player->getMoveCount());
                } else if (_moveCounts[count] > _player->getMoveCount()) {
                    _moveCounts[count] = _player->getMoveCount();
                }
                writeSave();
                setLevelNames(_currentLayer);
            }
            _menu->setOptions(_levelNames, -1, _itemsSelected.back());
            _itemsSelected.pop_back();
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

        if (glfwGetKey(_window, GLFW_KEY_ESCAPE) && _menu->isStill()) {
            previousOption();
        }

        _menu->update(_deltaTime);
        if (_menu->result() != -1) {
            selectOption(_menu->result());
        }
    }
    cameraDistance = cameraDistance*std::max(std::max((800.0f/_screenWidth), (600.0f/_screenHeight)*0.5f), 0.6f)*std::max(_screenHeight/600.0f, 0.6f);

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

void Game::writeSave() {
    std::ofstream file("save");
    for (int i = 0; i < _beatLevels.size(); i++) {
        file << _beatLevels[i] << " " << _moveCounts[i] << std::endl;
    }
}

void Game::loadSave() {
    std::ifstream file("save");
    if (file) {
        while (!file.eof()) {
            std::string fileName;
            file >> fileName;
            _beatLevels.push_back(fileName);
            int m;
            file >> m;
            _moveCounts.push_back(m);
        }
        _beatLevels.pop_back();
        _moveCounts.pop_back();
    }
}

void Game::draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _renderer->getShader()->use();

    glUniform3f(
        _renderer->getShader()->getUniformLocation("cameraPosition"), 
        _cameraPos.x,
        _cameraPos.y,
        _cameraPos.z
    );

    if (_state == GLOBAL::STATE_PLAY) {
        _floor->draw(_projectionViewMatrix);
        _player->draw(_projectionViewMatrix);
        _renderer->drawText("ZX: SELECT BLOCK", 20, 20, -1, GLOBAL::TEXT_COLOR);
        _renderer->drawTextCenter("WASD: MOVE", 0, 20, -1, GLOBAL::TEXT_COLOR);
        _renderer->drawTextRight("QE: ROTATE CAMERA", 20, 20, -1, GLOBAL::TEXT_COLOR);
        _renderer->drawTextRightTop("ESC: BACK", 20, 38, -1, GLOBAL::TEXT_COLOR);
        _renderer->drawTextRightTop("R: RESTART", 20, 75, -1, GLOBAL::TEXT_COLOR);
    } else if (_state == GLOBAL::STATE_MENU) {
        _menu->draw(_projectionViewMatrix);
        _renderer->drawText("A: LEFT", 20, 20, -1, GLOBAL::TEXT_COLOR);
        _renderer->drawTextCenter("W: SELECT", 0, 20, -1, GLOBAL::TEXT_COLOR);
        _renderer->drawTextRight("D: RIGHT", 20, 20, -1, GLOBAL::TEXT_COLOR);
        _renderer->drawTextRightTop("ESC: BACK", 20, 38, -1, GLOBAL::TEXT_COLOR);
    }

    glfwSwapBuffers(_window);
}