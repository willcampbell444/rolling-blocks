#include <levelEdit.h>

LevelEdit::LevelEdit(std::string fileName) {
    _fileName = fileName;
    if (std::ifstream(fileName)) {
        std::cout << "Modifying existing map" << std::endl;
        Map map;
        map.read(fileName.c_str());

        for (int w = 0; w < map.getWidth(); w++) {
            _tiles.push_back(std::vector<int>());
            for (int h = 0; h < map.getLength(); h++) {
                _tiles[w].push_back(map.getTiles()[w*map.getLength() + h]);
            }
        }

        _player = map.getStartPosition();
    } else {
        std::cout << "Creating new map" << std::endl;
    }

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_SAMPLES, 8);

    _window = glfwCreateWindow(GLOBAL::WINDOW_WIDTH, GLOBAL::WINDOW_HEIGHT, "OpenGL", nullptr, nullptr);

    glfwMakeContextCurrent(_window);

    glewExperimental = GL_TRUE;
    glewInit();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);

    glClearColor(GLOBAL::BACKGROUND.r, GLOBAL::BACKGROUND.g, GLOBAL::BACKGROUND.b, 1.0f);

    _renderer = new Renderer();

    _projectionMatrix = glm::perspective(glm::radians(50.0f), 800.0f / 600.0f, 1.0f, 50.0f);

    _cameraPos = glm::vec3(5, 5, 0);
}

bool LevelEdit::end() {
    return false;
}

GLFWwindow* LevelEdit::getWindow() {
    return _window;
}

void LevelEdit::update() {
    glfwPollEvents();

    if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(_window, GL_TRUE);
    }

    if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS) {
        _cameraPos.z += 0.1f*sin(glm::radians(_viewAngle-90));
        _cameraPos.x += 0.1f*cos(glm::radians(_viewAngle-90));
    }
    if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS) {
        _cameraPos.z -= 0.1f*sin(glm::radians(_viewAngle-90));
        _cameraPos.x -= 0.1f*cos(glm::radians(_viewAngle-90));
    }
    if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS) {
        _cameraPos.z += 0.1f*sin(glm::radians(_viewAngle));
        _cameraPos.x += 0.1f*cos(glm::radians(_viewAngle));
    }
    if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS) {
        _cameraPos.z -= 0.1f*sin(glm::radians(_viewAngle));
        _cameraPos.x -= 0.1f*cos(glm::radians(_viewAngle));
    }
    if (glfwGetKey(_window, GLFW_KEY_UP) == GLFW_PRESS) {
        _cameraPos.y += 0.1f;
    }
    if (glfwGetKey(_window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        _cameraPos.y -= 0.1f;
    }
    if (glfwGetKey(_window, GLFW_KEY_E) == GLFW_PRESS) {
        _viewAngle += 2;
    }
    if (glfwGetKey(_window, GLFW_KEY_Q) == GLFW_PRESS) {
        _viewAngle -= 2;
    }

    _viewMatrix = glm::lookAt(
        _cameraPos,
        glm::vec3(_cameraPos.x+10*cos(glm::radians(_viewAngle)), 0, _cameraPos.z+10*sin(glm::radians(_viewAngle))),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );

    double x, y;
    glfwGetCursorPos(_window, &x, &y);
    if (x > 0 && x < GLOBAL::WINDOW_WIDTH && y > 0 && y < GLOBAL::WINDOW_HEIGHT) {
        _mouseOn = true;
        x = x / GLOBAL::WINDOW_WIDTH;
        x = (2*x)-1;
        y = y / GLOBAL::WINDOW_HEIGHT;
        y = -((2*y)-1);
        glm::vec4 ray = glm::vec4(x, y, -1, 1);
        ray = glm::inverse(_projectionMatrix) * ray;
        ray = glm::vec4(ray.x, ray.y, -1, 0);
        _selected = glm::vec3(glm::inverse(_viewMatrix) * ray);
        _selected = glm::normalize(_selected);
        _selected = _cameraPos - ((_cameraPos.y+GLOBAL::GAP)/_selected.y)*_selected;
        _selected.x = round(_selected.x);
        _selected.z = round(_selected.z);
    } else {
        _mouseOn = false;
    }

    _projectionViewMatrix = _projectionMatrix * _viewMatrix;
}

void LevelEdit::draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _renderer->getShader()->use();

    glUniform3f(
        _renderer->getShader()->getUniformLocation("cameraPosition"), 
        _cameraPos.x,
        _cameraPos.y,
        _cameraPos.z
    );

    for (int w = 0; w < _tiles.size(); w++) {
        for (int l = 0; l < _tiles[w].size(); l++) {
            if (_tiles[w][l] == 1) {
                _renderer->drawFloorTile(_projectionViewMatrix, w, l);
            } else if (_tiles[w][l] == 2) {
                _renderer->drawVictoryTile(_projectionViewMatrix, w, l);
            }
        }
    }

    for (auto peice: _player) {
        _renderer->drawBox(_projectionViewMatrix, peice.x, peice.y, peice.z, GLOBAL::PLAYER_COLOR);
    }

    if (_mouseOn) {
        _renderer->drawBox(_projectionViewMatrix, _selected.x, _selected.y, _selected.z, GLOBAL::VICTORY_COLOR);
    }

    glfwSwapBuffers(_window);
}