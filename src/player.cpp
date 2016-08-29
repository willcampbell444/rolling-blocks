#include <player.h>

Player::Player(Shaders* shader, int w, int l) {
    _floorWidth = w;
    _floorLength = l;

    _shader = shader;

    float vertices[48] = {
        -0.5,  0.5,  -0.5, 0.752941, 0.772549, 0.8078431,
        -0.5,  0.5,   0.5, 0.752941, 0.772549, 0.8078431,
         0.5,  0.5,   0.5, 0.752941, 0.772549, 0.8078431,
         0.5,  0.5,  -0.5, 0.752941, 0.772549, 0.8078431,

        -0.5,  -0.5,  -0.5, 0.752941, 0.772549, 0.8078431,
        -0.5,  -0.5,   0.5, 0.752941, 0.772549, 0.8078431,
         0.5,  -0.5,   0.5, 0.752941, 0.772549, 0.8078431,
         0.5,  -0.5,  -0.5, 0.752941, 0.772549, 0.8078431,
    };

    GLuint elements[36] = {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4,
        4, 5, 1, 1, 0, 4,
        6, 7, 3, 3, 2, 6,
        4, 0, 3, 3, 7, 4,
        5, 1, 2, 2, 6, 5
    };

    GLuint lineElements[24] = {
        0, 1, 1, 2, 2, 3, 3, 0,
        4, 5, 5, 6, 6, 7, 7, 4,
        0, 4, 1, 5, 2, 6, 3, 7
    };

    glGenVertexArrays(1, &_vertexArrayObject);
    glBindVertexArray(_vertexArrayObject);

    glGenBuffers(1, &_elementBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*36, elements, GL_STATIC_DRAW);

    glGenBuffers(1, &_vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*8*6, vertices, GL_STATIC_DRAW);

    GLuint attrib = _shader->getAttributeLocation("position");
    glEnableVertexAttribArray(attrib);
    glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), 0);

    attrib = _shader->getAttributeLocation("color");
    glEnableVertexAttribArray(attrib);
    glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));



    glGenVertexArrays(1, &_lineVertexArrayObject);
    glBindVertexArray(_lineVertexArrayObject);

    glGenBuffers(1, &_lineElementBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _lineElementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*36, lineElements, GL_STATIC_DRAW);

    for (int i = 0; i < 8; i++) {
        vertices[i*6+3] = 0;
        vertices[i*6+4] = 0;
        vertices[i*6+5] = 0;
    }

    glGenBuffers(1, &_lineVertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, _lineVertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*8*6, vertices, GL_STATIC_DRAW);

    attrib = _shader->getAttributeLocation("position");
    glEnableVertexAttribArray(attrib);
    glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), 0);

    attrib = _shader->getAttributeLocation("color");
    glEnableVertexAttribArray(attrib);
    glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));

    _rotationAxis = glm::vec3(0, 0, 1);

    _playerPeices.push_back(glm::vec3(0, 0, 0));
    // _playerPeices.push_back(glm::vec3(0, 0, 1));
    _playerPeices.push_back(glm::vec3(1, 0, 0));
    _playerPeices.push_back(glm::vec3(1, 0, 1));
    _playerPeices.push_back(glm::vec3(0, 1, 0));
    // _playerPeices.push_back(glm::vec3(0, 1, 1));
    // _playerPeices.push_back(glm::vec3(1, 1, 0));
    _playerPeices.push_back(glm::vec3(1, 1, 1));
    _playerPeices.push_back(glm::vec3(0, 2, 0));
    _playerPeices.push_back(glm::vec3(0, 2, 1));
    // _playerPeices.push_back(glm::vec3(1, 2, 0));
    _playerPeices.push_back(glm::vec3(1, 2, 1));

    _nextPeices = _playerPeices;

    setMinMax();

    _cameraPos = glm::vec3(
        -(_floorWidth/2.0f)+(_minX+_maxX+1)/2.0f,
        (_minY+_maxY+1)/2.0f,
        -(_floorLength/2.0f)+(_minZ+_maxZ+1)/2.0f
    );
}

void Player::setMinMax() {
    _minX =  999999;
    _minY =  999999;
    _minZ =  999999;
    _maxX = -999999;
    _maxY = -999999;
    _maxZ = -999999;
    for (auto peice: _nextPeices) {
        if (peice.x < _minX) {
            _minX = peice.x;
        }
        if (peice.x > _maxX) {
            _maxX = peice.x;
        }
        if (peice.y < _minY) {
            _minY = peice.y;
        }
        if (peice.y > _maxY) {
            _maxY = peice.y;
        }
        if (peice.z < _minZ) {
            _minZ = peice.z;
        }
        if (peice.z > _maxZ) {
            _maxZ = peice.z;
        }
    }
}

void Player::move(int x, int z) {
    if (!_isTransition && _playerPeices.size()) {
        _isTransition = true;
        _angle = 0.0f;
        _rotationAxis = glm::vec3(z, 0, x);
        _frame = 0;
        _oldCameraPos = _cameraPos;
        _nextPeices = _playerPeices;

        setMinMax();

        if (x == 1) {
            for (int i = 0; i < _nextPeices.size(); i++) {
                _nextPeices[i].x = _maxX+_playerPeices[i].y+1;
                _nextPeices[i].y = _maxX-_playerPeices[i].x;
            }
            _angleSign = -1;
            _rotationAxisPosition = glm::vec3(_floorWidth/2.0f - _maxX - 1, 0, 0);
        } else if (x == -1) {
            for (int i = 0; i < _nextPeices.size(); i++) {
                _nextPeices[i].x = _minX-_playerPeices[i].y-1;
                _nextPeices[i].y = _playerPeices[i].x-_minX;
            }
            _angleSign = -1;
            _rotationAxisPosition = glm::vec3(_floorWidth/2.0f - _minX, 0, 0);
        }
        if (z == 1) {
            for (int i = 0; i < _nextPeices.size(); i++) {
                _nextPeices[i].z = _maxZ+_playerPeices[i].y+1;
                _nextPeices[i].y = _maxZ-_playerPeices[i].z;
            }
            _angleSign = 1;
            _rotationAxisPosition = glm::vec3(0, 0, _floorLength/2.0f - _maxZ - 1);
        } else if (z == -1) {
            for (int i = 0; i < _nextPeices.size(); i++) {
                _nextPeices[i].z = _minZ-_playerPeices[i].y-1;
                _nextPeices[i].y = _playerPeices[i].z-_minZ;
            }
            _angleSign = 1;
            _rotationAxisPosition = glm::vec3(0, 0, _floorLength/2.0f - _minZ);
        }

        setMinMax();

        // std::cout << _minZ << ", " << _maxZ << ", " << (_minZ+_maxZ+1)/2.0f << std::endl;
        _newCameraPos = glm::vec3(
            -(_floorWidth/2.0f)+(_minX+_maxX+1)/2.0f,
            (_minY+_maxY+1)/2.0f,
            -(_floorLength/2.0f)+(_minZ+_maxZ+1)/2.0f
        );
    }
}

void Player::update(unsigned char* map) {
    if (_isTransition) {
        _frame += 1;
        float mu = _frame/50.0f;
        mu = ((mu) * (mu) * (3 - 2 * (mu)));
        _angle = 90.0f*mu;
        _cameraPos = _oldCameraPos*(1.0f-mu) + _newCameraPos*mu;
        if (_frame >= 50) {
            _playerPeices = _nextPeices;
            _isTransition = false;
            _frame = 0;
            _angle = 0.0f;
        }
        for (int i = 0; i < _playerPeices.size(); i++) {
            if (_playerPeices[i].x < 0 
                || _playerPeices[i].x > _floorWidth-1 
                || _playerPeices[i].z < 0 
                || _playerPeices[i].z > _floorLength-1
                || map[(int)(_playerPeices[i].x*_floorLength + _playerPeices[i].z)] == 0
            ) {
                _falling.push_back(glm::vec4(_playerPeices[i].x, _playerPeices[i].y, _playerPeices[i].z, 2));
                _playerPeices.erase(_playerPeices.begin() + i);
                i -= 1;
            }
        }
    }
    for (int i = 0; i < _falling.size(); i++) {
        _falling[i][3] += 1;
        if (_falling[i][3] > 1000) {
            _falling.erase(_falling.begin() + i);
        }
    }
}

void Player::draw(glm::mat4 viewProjectionMatrix) {
    _shader->use();
    for (glm::vec3 peice: _playerPeices) {
        _transformMatrix = viewProjectionMatrix
        * glm::translate(glm::mat4(1.0f), -_rotationAxisPosition)
        * glm::rotate(glm::mat4(1.0f), glm::radians(_angleSign*_angle), _rotationAxis)
        * glm::translate(glm::mat4(1.0f), _rotationAxisPosition)
        * glm::scale(glm::mat4(1.0f), glm::vec3(0.90f, 0.90f, 0.90f))
        * glm::translate(
            glm::mat4(1.0f), 
            glm::vec3(
                (-(_floorWidth/2.0f) + peice.x + 0.5f) * (1.0/0.9),
                (0.5f + peice.y) * (1.0/0.9),
                (-(_floorLength/2.0f) + peice.z + 0.5f) * (1.0/0.9)
            )
        );
        glUniformMatrix4fv(
            _shader->getUniformLocation("transformMatrix"), 
            1, 
            GL_FALSE, 
            glm::value_ptr(_transformMatrix)
        );
        glBindVertexArray(_vertexArrayObject);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glBindVertexArray(_lineVertexArrayObject);
        glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);
    }
    for (glm::vec4 peice: _falling) {
        _transformMatrix = viewProjectionMatrix
        * glm::scale(glm::mat4(1.0f), glm::vec3(0.90f, 0.90f, 0.90f))
        * glm::translate(
            glm::mat4(1.0f), 
            glm::vec3(
                (-(_floorWidth/2.0f) + peice.x + 0.5f) * (1.0/0.9),
                (0.5f + peice.y - peice[3]*peice[3]*0.005) * (1.0/0.9),
                (-(_floorLength/2.0f) + peice.z + 0.5f) * (1.0/0.9)
            )
        );
        glUniformMatrix4fv(
            _shader->getUniformLocation("transformMatrix"), 
            1, 
            GL_FALSE, 
            glm::value_ptr(_transformMatrix)
        );
        glBindVertexArray(_vertexArrayObject);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glBindVertexArray(_lineVertexArrayObject);
        glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);
    }
}

glm::vec3 Player::getCameraPos() {
    return _cameraPos;
}