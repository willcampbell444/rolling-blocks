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


    _direction = glm::vec3(0, 1, 0);
    _rotationAxis = glm::vec3(0, 0, 1);
    _cameraPos = glm::vec3(
        (-(_floorWidth/2.0f)+_x+((_height/2.0f)*_direction.x)-(_direction.x/2.0f) + 0.5f),
        (-(_direction.y/2.0f)+0.5f+((_height/2.0f)*_direction.y)),
        (-(_floorLength/2.0f)+_z+((_height/2.0f)*_direction.z)-(_direction.z/2.0f)+0.5f)
    );

    _playerPeices.push_back(glm::vec3(0, 0, 0));
    _playerPeices.push_back(glm::vec3(0, 1, 0));
    _playerPeices.push_back(glm::vec3(0, 1, 1));


}

void Player::setMinMax() {
    _minX = 999999;
    _minY = 999999;
    _minZ = 999999;
    _maxX = 0;
    _maxY = 0;
    _maxZ = 0;
    for (auto peice: _playerPeices) {
        if (peice.x < _minX) {
            _minX = peice.x;
        }
        if (peice.x > _maxX) {
            _maxX = peice.x
        }
        if (peice.y < _minY) {
            _minY = peice.y;
        }
        if (peice.y > _maxY) {
            _maxY = peice.y
        }
        if (peice.z < _minZ) {
            _minZ = peice.x;
        }
        if (peice.z > _maxZ) {
            _maxZ = peice.z;
        }
    }
}

void Player::move(int x, int z) {
    if (!_isTransition) {
        _isTransition = true;
        _angle = 0.0f;
        _rotationAxis = glm::vec3(z, 0, x);
        _frame = 0;
        _oldCameraPos = glm::vec3(
            (-(_floorWidth/2.0f)+_x+((_height/2.0f)*_direction.x)-(_direction.x/2.0f) + 0.5f),
            (-(_direction.y/2.0f)+0.5f+((_height/2.0f)*_direction.y)),
            (-(_floorLength/2.0f)+_z+((_height/2.0f)*_direction.z)-(_direction.z/2.0f)+0.5f)
        );
        _nextPeices = _playerPeices;

        setMinMax();

        if (x == 1) {
            for (glm::vec3 peice: _nextPeices) {
                peice.x += peice.y+1;
                peice.y = maxX-peice.x;

                _angleSign = std::abs(z)*2 - 1;
                _rotationAxisPosition = glm::vec3(
                    std::abs(x)*(_floorWidth/2.0f - _maxX - (x/2.0f + 0.5f)),
                    0,
                    std::abs(z)*(_floorLength/2.0f - _maxZ - (z/2.0f + 0.5f))
                );
            }
        } else if (x == -1) {
            for (glm::vec3 peice: _nextPeices) {
                peice.x += peice.y+1;
                peice.y = maxX-peice.x;

                _angleSign = std::abs(z)*2 - 1;
                _rotationAxisPosition = glm::vec3(
                    std::abs(x)*(_floorWidth/2.0f - _minX - (x/2.0f + 0.5f)),
                    0,
                    std::abs(z)*(_floorLength/2.0f - _maxZ - (z/2.0f + 0.5f))
                );
            }
        }

        // if (_direction.y) {
        //     _nextDirection = glm::vec3(x, 0, z);
        //     _nextX = _x+x;
        //     _nextZ = _z+z;

        //     _angleSign = std::abs(z)*2 - 1;
        //     _rotationAxisPosition = glm::vec3(
        //         std::abs(x)*(_floorWidth/2.0f - _x - (x/2.0f + 0.5f)),
        //         0,
        //         std::abs(z)*(_floorLength/2.0f - _z - (z/2.0f + 0.5f))
        //     );
        // } else {
        //     if ((_direction.x == x && x) || (_direction.z == z && z)) {
        //         _nextDirection = glm::vec3(0, 1, 0);
        //         _nextX = _x+(x*_height);
        //         _nextZ = _z+(z*_height);

        //         _angleSign = std::abs(z)*2 - 1;
        //         _rotationAxisPosition = glm::vec3(
        //             std::abs(x)*(_floorWidth/2.0f - (_x+(x*(_height-1))) - (x/2.0f + 0.5f)),
        //             0,
        //             std::abs(z)*(_floorLength/2.0f - (_z+(z*(_height-1))) - (z/2.0f + 0.5f))
        //         );
        //     } else if ((_direction.x && x) || (_direction.z && z)) {
        //         _nextDirection = glm::vec3(0, 1, 0);
        //         _nextX = _x+x;
        //         _nextZ = _z+z;

        //         _angleSign = std::abs(z)*2 - 1;
        //         _rotationAxisPosition = glm::vec3(
        //             std::abs(x)*(_floorWidth/2.0f - _x - (x/2.0f + 0.5f)),
        //             0,
        //             std::abs(z)*(_floorLength/2.0f - _z - (z/2.0f + 0.5f))
        //         );
        //     } else {
        //         _nextX = _x+x;
        //         _nextZ = _z+z;

        //         _angleSign = std::abs(z)*2 - 1;
        //         _rotationAxisPosition = glm::vec3(
        //             std::abs(x)*(_floorWidth/2.0f - _x - (x/2.0f + 0.5f)),
        //             0,
        //             std::abs(z)*(_floorLength/2.0f - _z - (z/2.0f + 0.5f))
        //         );
        //     }
        // }
        _newCameraPos = glm::vec3(
            (-(_floorWidth/2.0f)+_nextX+((_height/2.0f)*_nextDirection.x)-(_nextDirection.x/2.0f) + 0.5f),
            (-(_nextDirection.y/2.0f) + 0.5f+((_height/2.0f)*_nextDirection.y)),
            -(_floorLength/2.0f)+_nextZ+((_height/2.0f)*_nextDirection.z)-(_nextDirection.z/2.0f)+0.5f
        );
    }
}

void Player::update() {
    if (_isTransition) {
        _frame += 1;
        float mu = _frame/50.0f;
        mu = ((mu) * (mu) * (3 - 2 * (mu)));
        _angle = 90.0f*mu;
        _cameraPos = _oldCameraPos*(1.0f-mu) + _newCameraPos*mu;
        if (_frame >= 50) {
            _x = _nextX;
            _z = _nextZ;
            _direction = _nextDirection;
            _isTransition = false;
            _frame = 0;
            _angle = 0.0f;
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
                (-(_floorWidth/2.0f) + _x+peice.x + 0.5f) * (1.0/0.9),
                (0.5f + peice.y) * (1.0/0.9),
                (-(_floorLength/2.0f) + _z+peice.z + 0.5f) * (1.0/0.9)
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