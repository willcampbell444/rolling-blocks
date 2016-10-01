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

    _gray = glm::vec3(0.752941, 0.772549, 0.8078431);

    if (!_shaders[0].loadShader(GL_VERTEX_SHADER, "shaders/vertex.glsl")) {
        std::cout << "Vertex Shader Failed To Compile";
    }
    if (!_shaders[0].loadShader(GL_FRAGMENT_SHADER, "shaders/fragment.glsl")) {
        std::cout << "Fragment Shader Failed To Compile";
    }
    _shaders[0].createProgram();

    _shaders[0].use();

    _projectionMatrix = glm::perspective(glm::radians(50.0f), 800.0f / 600.0f, 1.0f, 50.0f);

    glClearColor(GLOBAL::BACKGROUND.r, GLOBAL::BACKGROUND.g, GLOBAL::BACKGROUND.b, 1.0f);

    _floor = new Floor(&_shaders[0]);
    _player = new Player(&_shaders[0]);

    _levelMapNames.push_back("maps/test2.map");
    _levelMapNames.push_back("maps/test.map");
    _levelMapNames.push_back("maps/test2.map");
    _levelMapNames.push_back("maps/test.map");

    loadMap();
}

Game::~Game() {
    glDeleteBuffers(2, _vbo);
    glDeleteBuffers(1, _ebo);
    glDeleteVertexArrays(2, _vao);

    delete _floor;
    delete _player;

    glfwTerminate();
}

GLFWwindow* Game::getWindow() {
    return _window;
}

bool Game::end() {
    return _end;
}

void Game::loadMap() {
    if (_level == _levelMapNames.size()) {
        _end = true;
        return;
    }
    _map.read(_levelMapNames[_level]);
    _level += 1;

    _floor->create(_map.getWidth(), _map.getLength(), _map.getTiles());
    _player->create(_map.getWidth(), _map.getLength(), _map.getStartPosition());

    _cameraAngle = 0.0f;
    _cameraHeight = 0.0f;
}

void Game::update() {
    glfwPollEvents();

    if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(_window, GL_TRUE);
    }

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

    if (_cameraAngle > 360) {
        _cameraAngle = 0;
    } else if (_cameraAngle < 0) {
        _cameraAngle = 360;
    }

    _player->update(_map.getTiles(), _map.getVictoryTiles());

    glm::vec3 cameraPos = _player->getCameraPos();
    glm::vec2 cameraDistance = _player->getCameraDistance();

    _viewMatrix = glm::lookAt(
        glm::vec3(
            cameraPos.x - std::cos(_cameraAngle*(3.14159/180))*cameraDistance.x,
            cameraPos.y + cameraDistance.y + _cameraHeight,
            cameraPos.z - std::sin(_cameraAngle*(3.14159/180))*cameraDistance.x
        ),
        cameraPos,
        glm::vec3(0.0f, 1.0f, 0.0f)
    );

    _projectionViewMatrix = _projectionMatrix * _viewMatrix;
    
    if (_player->win()) {
        loadMap();
        if (_end) {
            return;
        }
    }
}

void Game::draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _shaders[0].use();
    _floor->draw(_projectionViewMatrix);
    _player->draw(_projectionViewMatrix);

    glfwSwapBuffers(_window);
}