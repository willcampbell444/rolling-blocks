#include <player.h>

Player::Player(Shaders* shader) {
    _shader = shader;

    float vertices[48] = {
        -0.5,  0.5,  -0.5, GLOBAL::PLAYER_COLOR.r, GLOBAL::PLAYER_COLOR.g, GLOBAL::PLAYER_COLOR.b,
        -0.5,  0.5,   0.5, GLOBAL::PLAYER_COLOR.r, GLOBAL::PLAYER_COLOR.g, GLOBAL::PLAYER_COLOR.b,
         0.5,  0.5,   0.5, GLOBAL::PLAYER_COLOR.r, GLOBAL::PLAYER_COLOR.g, GLOBAL::PLAYER_COLOR.b,
         0.5,  0.5,  -0.5, GLOBAL::PLAYER_COLOR.r, GLOBAL::PLAYER_COLOR.g, GLOBAL::PLAYER_COLOR.b,

        -0.5,  -0.5,  -0.5, GLOBAL::PLAYER_COLOR.r, GLOBAL::PLAYER_COLOR.g, GLOBAL::PLAYER_COLOR.b,
        -0.5,  -0.5,   0.5, GLOBAL::PLAYER_COLOR.r, GLOBAL::PLAYER_COLOR.g, GLOBAL::PLAYER_COLOR.b,
         0.5,  -0.5,   0.5, GLOBAL::PLAYER_COLOR.r, GLOBAL::PLAYER_COLOR.g, GLOBAL::PLAYER_COLOR.b,
         0.5,  -0.5,  -0.5, GLOBAL::PLAYER_COLOR.r, GLOBAL::PLAYER_COLOR.g, GLOBAL::PLAYER_COLOR.b,
    };

    float doneVertices[48] = {
        -0.5,  0.5,  -0.5, GLOBAL::DONE_PLAYER_COLOR.r, GLOBAL::DONE_PLAYER_COLOR.g, GLOBAL::DONE_PLAYER_COLOR.b,
        -0.5,  0.5,   0.5, GLOBAL::DONE_PLAYER_COLOR.r, GLOBAL::DONE_PLAYER_COLOR.g, GLOBAL::DONE_PLAYER_COLOR.b,
         0.5,  0.5,   0.5, GLOBAL::DONE_PLAYER_COLOR.r, GLOBAL::DONE_PLAYER_COLOR.g, GLOBAL::DONE_PLAYER_COLOR.b,
         0.5,  0.5,  -0.5, GLOBAL::DONE_PLAYER_COLOR.r, GLOBAL::DONE_PLAYER_COLOR.g, GLOBAL::DONE_PLAYER_COLOR.b,

        -0.5,  -0.5,  -0.5, GLOBAL::DONE_PLAYER_COLOR.r, GLOBAL::DONE_PLAYER_COLOR.g, GLOBAL::DONE_PLAYER_COLOR.b,
        -0.5,  -0.5,   0.5, GLOBAL::DONE_PLAYER_COLOR.r, GLOBAL::DONE_PLAYER_COLOR.g, GLOBAL::DONE_PLAYER_COLOR.b,
         0.5,  -0.5,   0.5, GLOBAL::DONE_PLAYER_COLOR.r, GLOBAL::DONE_PLAYER_COLOR.g, GLOBAL::DONE_PLAYER_COLOR.b,
         0.5,  -0.5,  -0.5, GLOBAL::DONE_PLAYER_COLOR.r, GLOBAL::DONE_PLAYER_COLOR.g, GLOBAL::DONE_PLAYER_COLOR.b,
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

    GLuint elementBufferObject;
    GLuint vertexBufferObject;

    glGenVertexArrays(1, &_vertexArrayObject);
    glBindVertexArray(_vertexArrayObject);

    glGenBuffers(1, &elementBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*36, elements, GL_STATIC_DRAW);

    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*8*6, vertices, GL_STATIC_DRAW);

    GLuint attrib = _shader->getAttributeLocation("position");
    glEnableVertexAttribArray(attrib);
    glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), 0);

    attrib = _shader->getAttributeLocation("color");
    glEnableVertexAttribArray(attrib);
    glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));



    glGenVertexArrays(1, &_doneVertexArrayObject);
    glBindVertexArray(_doneVertexArrayObject);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);

    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*8*6, doneVertices, GL_STATIC_DRAW);

    attrib = _shader->getAttributeLocation("position");
    glEnableVertexAttribArray(attrib);
    glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), 0);

    attrib = _shader->getAttributeLocation("color");
    glEnableVertexAttribArray(attrib);
    glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));



    glGenVertexArrays(1, &_lineVertexArrayObject);
    glBindVertexArray(_lineVertexArrayObject);

    glGenBuffers(1, &elementBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*36, lineElements, GL_STATIC_DRAW);

    for (int i = 0; i < 8; i++) {
        vertices[i*6+3] = 0;
        vertices[i*6+4] = 0;
        vertices[i*6+5] = 0;
    }

    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*8*6, vertices, GL_STATIC_DRAW);

    attrib = _shader->getAttributeLocation("position");
    glEnableVertexAttribArray(attrib);
    glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), 0);

    attrib = _shader->getAttributeLocation("color");
    glEnableVertexAttribArray(attrib);
    glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));
}

void Player::create(int x, int y, unsigned char* map, std::vector<glm::vec3> startPosition) {
    _floorWidth = x;
    _floorLength = y;
    
    _heightMap.create(_floorWidth, _floorLength);

    _static.clear();
    _falling.clear();
    _done.clear();
    _endTimer = 0;

    _rotationAxis = glm::vec3(0, 0, 1);

    _playerPeices = startPosition;
    _newPeices = _playerPeices;
    gravity();
    sever();

    onWinTile(map);
    _playerPeices = _newPeices;

    for (int i = 0; i < _playerPeices.size(); i++) {
        if (map[(int)(_playerPeices[i].x*_floorLength + _playerPeices[i].z)] == 2) {
            _done.push_back(glm::vec4(_playerPeices[i].x, _playerPeices[i].y, _playerPeices[i].z, 2));
            _playerPeices.erase(_playerPeices.begin() + i);
            i -= 1;
        }
    }

    setMinMax();

    _cameraPos = glm::vec3(
        -(_floorWidth/2.0f)+(_minX+_maxX+1)/2.0f,
        (_minY+_maxY+1)/2.0f,
        -(_floorLength/2.0f)+(_minZ+_maxZ+1)/2.0f
    );

    if (_maxX - _minX > _maxZ - _minZ) {
        _cameraDistance.x = _maxX - _minX + 5;
    } else {
        _cameraDistance.x = _maxZ - _minZ + 5;
    }
    _cameraDistance.y = _maxY - _minY + 3;
}

bool Player::win() {
    if (_playerPeices.size() == 0 || _won) {
        _isTransition = false;
        _isCameraTransition = false;
        _endTimer += 1;
        if (_endTimer == 150) {
            return true;
        }
    }
    return false;
}

void Player::checkVictory(std::vector<glm::vec2> victoryTiles) {
    for (int i = 0; i < victoryTiles.size(); i++) {
        for (glm::vec3 peice: _done) {
            if (peice.x == victoryTiles[i].x && peice.z == victoryTiles[i].y) {
                victoryTiles.erase(victoryTiles.begin() + i);
                i -= 1;
            }
        }
    }
    if (victoryTiles.size() == 0) {
        _won = true;
    }
}

void Player::fillHeightMap() {
    for (int i = 0; i < _floorWidth; i++) {
        for (int j = 0; j < _floorLength; j++) {
            _heightMap[i][j] = 0;
        }
    }
    for (glm::vec3 peice: _static) {
        _heightMap[(int)peice.x][(int)peice.z] += 1;
    }
    for (glm::vec3 peice: _done) {
        _heightMap[(int)peice.x][(int)peice.z] += 1;
    }
}

void Player::setMinMax() {
    _minX =  999999;
    _minY =  999999;
    _minZ =  999999;
    _maxX = -999999;
    _maxY = -999999;
    _maxZ = -999999;
    for (auto peice: _playerPeices) {
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

void Player::move(int x, int z, unsigned char* map) {
    if (!_isTransition && _playerPeices.size() && !_isCameraTransition) {
        fillHeightMap();
        _isTransition = true;
        _angle = 90.0f;
        _rotationAxis = glm::vec3(z, 0, x);
        _frame = 0;
        _oldCameraPos = _cameraPos;
        _oldCameraDistance = _cameraDistance;
        _newPeices = _playerPeices;

        setMinMax();

        if (x == 1) {
            for (int i = 0; i < _newPeices.size(); i++) {
                _newPeices[i].x = _maxX+_playerPeices[i].y+1;
                _newPeices[i].y = _maxX-_playerPeices[i].x;
            }
            _angleSign = 1;
            _rotationAxisPosition = glm::vec3(_floorWidth/2.0f - _maxX - 1, 0, 0);
        } else if (x == -1) {
            for (int i = 0; i < _newPeices.size(); i++) {
                _newPeices[i].x = _minX-_playerPeices[i].y-1;
                _newPeices[i].y = _playerPeices[i].x-_minX;
            }
            _angleSign = 1;
            _rotationAxisPosition = glm::vec3(_floorWidth/2.0f - _minX, 0, 0);
        }
        if (z == 1) {
            for (int i = 0; i < _newPeices.size(); i++) {
                _newPeices[i].z = _maxZ+_playerPeices[i].y+1;
                _newPeices[i].y = _maxZ-_playerPeices[i].z;
            }
            _angleSign = -1;
            _rotationAxisPosition = glm::vec3(0, 0, _floorLength/2.0f - _maxZ - 1);
        } else if (z == -1) {
            for (int i = 0; i < _newPeices.size(); i++) {
                _newPeices[i].z = _minZ-_playerPeices[i].y-1;
                _newPeices[i].y = _playerPeices[i].z-_minZ;
            }
            _angleSign = -1;
            _rotationAxisPosition = glm::vec3(0, 0, _floorLength/2.0f - _minZ);
        }

        _oldPeices = _playerPeices;
        _playerPeices = _newPeices;

        onBlock(x, z);
        gravity();

        _oldPeices = _playerPeices;

        onWinTile(map);
        setMinMax();

        _newCameraPos = glm::vec3(
            -(_floorWidth/2.0f)+(_minX+_maxX+1)/2.0f,
            (_minY+_maxY+1)/2.0f,
            -(_floorLength/2.0f)+(_minZ+_maxZ+1)/2.0f
        );

        if (_maxX - _minX > _maxZ - _minZ) {
            _newCameraDistance.x = _maxX - _minX + 5;
        } else {
            _newCameraDistance.x = _maxZ - _minZ + 5;
        }
        _newCameraDistance.y = _maxY - _minY + 3;
    }
}

void Player::onWinTile(unsigned char* map) {
    for (int i = 0; i < _newPeices.size(); i++) {
        if (map[(int)(_newPeices[i].x*_floorLength + _newPeices[i].z)] == 2) {
            _newPeices[i].y -= GLOBAL::GAP*4.0f;
        }
    }
}

void Player::gravity() {
    std::vector<glm::vec3> previous;
    std::vector<int> notDone;

    for (int i = 0; i < _newPeices.size(); i++) {
        notDone.push_back(i);
    }
    for (int i = 0; i < notDone.size(); i++) {
        if (_newPeices[notDone[i]].y == 0) {
            previous.push_back(_newPeices[notDone[i]]);
            notDone.erase(notDone.begin() + i);
            i -= 1;
        }
    }
    int level = 1;
    bool anyFalls = false;
    while (notDone.size() > 0) {
        for (int i = 0; i < notDone.size(); i++) {
            if (_newPeices[notDone[i]].y == level) {
                bool success = false;
                for (auto peice: previous) {
                    if (
                        (
                            _newPeices[notDone[i]].x == peice.x
                            && _newPeices[notDone[i]].y-1 == peice.y
                            && _newPeices[notDone[i]].z == peice.z
                        ) || (
                            _newPeices[notDone[i]].y
                            == _heightMap[
                                (int)_newPeices[notDone[i]].x
                            ][
                                (int)_newPeices[notDone[i]].z
                            ]
                        )
                    ) {
                        previous.push_back(_newPeices[notDone[i]]);
                        notDone.erase(notDone.begin() + i);
                        i -= 1;
                        success = true;
                        break;
                    }
                }
                if (!success) {
                    anyFalls = true;
                    _newPeices[notDone[i]].y -= 1;
                    notDone.erase(notDone.begin() + i);
                    i -= 1;
                }
            }
        }
        level += 1;
    }
    if (anyFalls) {
        gravity();
    }
}

void Player::onBlock(int x, int z) {
    float maxDistance, targetDistance;
    for (int i = 0; i < _newPeices.size(); i++) {
        maxDistance = (
            pow(_newPeices[i].y+1.0f, 2)
            + pow(
                (
                    _newPeices[i].x 
                    - (_minX*abs((x/2.0f-0.5f)) + _maxX*abs((x/2.0f+0.5f)))
                ) * x, 2)
            + pow(
                (
                    _newPeices[i].z
                    - (_minZ*abs((z/2.0f-0.5f)) + _maxZ*abs((z/2.0f+0.5f)))
                ) * z, 2)
        );
        for (int j = 1; (
            j <= _oldPeices[i].x - _newPeices[i].x
            || j <= _newPeices[i].x - _oldPeices[i].x
            || j <= _oldPeices[i].z - _newPeices[i].z
            || j <= _newPeices[i].z - _oldPeices[i].z
        ); j++) {
            targetDistance = (
                pow(_heightMap[(int)_oldPeices[i].x+(j*x)][(int)_oldPeices[i].z+(j*z)], 2)
                + pow(
                    (
                        (_oldPeices[i].x + j*x)
                        - (_minX*abs((x/2.0f-0.5f)) + _maxX*abs((x/2.0f+0.5f)))
                    ) * x, 2)
                + pow(
                    (
                        (_oldPeices[i].z + j*z)
                        - (_minZ*abs((z/2.0f-0.5f)) + _maxZ*abs((z/2.0f+0.5f)))
                    ) * z, 2)
            );
            if (targetDistance >= maxDistance) {
                _newPeices[i].x = _oldPeices[i].x + j*x - x;
                _newPeices[i].z = _oldPeices[i].z + j*z - z;
            }
        }

        _newPeices[i].y += _heightMap[(int)_newPeices[i].x][(int)_newPeices[i].z];
        bool movedUp = true;
        while (movedUp) {
            movedUp = false;
            for (glm::vec3 peice: _newPeices) {
            }
            for (int j = 0; j < i; j++) {
                if (_newPeices[j].x == _newPeices[i].x
                    && _newPeices[j].y == _newPeices[i].y 
                    && _newPeices[j].z == _newPeices[i].z
                ) {
                    movedUp = true;
                    _newPeices[i].y += 1;
                }
            }
            for (int j = i+1; j < _newPeices.size(); j++) {
                if (_newPeices[j].x == _newPeices[i].x
                    && _newPeices[j].y == _newPeices[i].y 
                    && _newPeices[j].z == _newPeices[i].z
                ) {
                    movedUp = true;
                    _newPeices[i].y += 1;
                }
            }
        }
    }
}

void Player::update(unsigned char* map, std::vector<glm::vec2> victoryTiles) {
    if (_isTransition) {
        _frame += 1;
        float mu = _frame/50.0f;
        mu = (mu * mu);
        _angle = 90.0f*(1-mu);
        for (int i = 0; i < _playerPeices.size(); i++) {
            _playerPeices[i].y = _oldPeices[i].y*(1-mu) + _newPeices[i].y*mu;
            _playerPeices[i].z = _oldPeices[i].z*(1-mu) + _newPeices[i].z*mu;
            _playerPeices[i].x = _oldPeices[i].x*(1-mu) + _newPeices[i].x*mu;
        }
        mu = _frame/50.0f;
        mu = (mu * mu * (3 - 2 * (mu)));
        _cameraPos = _oldCameraPos*(1.0f-mu) + _newCameraPos*mu;
        _cameraDistance = _oldCameraDistance*(1.0f-mu) + _newCameraDistance*mu;
        if (_frame >= 50) {
            _isTransition = false;
            _frame = 0;
            _angle = 0.0f;
            _playerPeices = _newPeices;
            for (int i = 0; i < _playerPeices.size(); i++) {
                if (_playerPeices[i].x < 0 
                    || _playerPeices[i].x > _floorWidth-1 
                    || _playerPeices[i].z < 0 
                    || _playerPeices[i].z > _floorLength-1
                    || map[(int)(_playerPeices[i].x*_floorLength + _playerPeices[i].z)] == 0
                ) {
                    _falling.push_back(glm::vec4(
                        _playerPeices[i].x,
                        _playerPeices[i].y,
                        _playerPeices[i].z,
                        2
                    ));
                    _playerPeices.erase(_playerPeices.begin() + i);
                    i -= 1;
                }
                if (map[(int)(_playerPeices[i].x*_floorLength + _playerPeices[i].z)] == 2) {
                    _done.push_back(glm::vec4(
                        _playerPeices[i].x,
                        _playerPeices[i].y,
                        _playerPeices[i].z,
                        2
                    ));
                    _playerPeices.erase(_playerPeices.begin() + i);
                    i -= 1;
                }
            }

            attach();
            sever();

            _oldCameraDistance = _newCameraDistance;
            _oldCameraPos = _newCameraPos;

            setMinMax();

            _newCameraPos = glm::vec3(
                -(_floorWidth/2.0f)+(_minX+_maxX+1)/2.0f,
                (_minY+_maxY+1)/2.0f,
                -(_floorLength/2.0f)+(_minZ+_maxZ+1)/2.0f
            );

            if (_maxX - _minX > _maxZ - _minZ) {
                _newCameraDistance.x = _maxX - _minX + 5;
            } else {
                _newCameraDistance.x = _maxZ - _minZ + 5;
            }
            _newCameraDistance.y = _maxY - _minY + 3;

            if (_oldCameraPos != _newCameraPos) {
                _isCameraTransition = true;
            }

            checkVictory(victoryTiles);
        }
    } else if (_isCameraTransition) {
        _frame += 1;
        float mu = _frame/50.0f;
        mu = (mu * mu * (3 - 2 * (mu)));
        _cameraPos = _oldCameraPos*(1.0f-mu) + _newCameraPos*mu;
        _cameraDistance = _oldCameraDistance*(1.0f-mu) + _newCameraDistance*mu;
        if (_frame >= 50) {
            _isCameraTransition = false;
            _oldCameraDistance = _newCameraDistance;
            _oldCameraPos = _newCameraPos;
            _frame = 0;
        }
    }
    for (int i = 0; i < _falling.size(); i++) {
        _falling[i][3] += 1;
        if (_falling[i][3] > 1000) {
            _falling.erase(_falling.begin() + i);
        }
    }
}

void Player::sever() {
    std::vector<int> playerGroups;
    std::vector<int> staticGroups;
    std::vector<int> groupCounts;
    for (int i = 0; i < _playerPeices.size(); i++) {
        playerGroups.push_back(i);
        groupCounts.push_back(1);
    }
    for (int i = 0; i < _static.size(); i++) {
        staticGroups.push_back(groupCounts.size());
        groupCounts.push_back(1);
    }

    for (int i = 0; i < _playerPeices.size(); i++) {
        for (int j = i+1; j < _playerPeices.size(); j++)
        {
            if (
                (
                    _playerPeices[i].x+1 == _playerPeices[j].x
                    && _playerPeices[i].y == _playerPeices[j].y
                    && _playerPeices[i].z == _playerPeices[j].z
                )
                || (
                    _playerPeices[i].x-1 == _playerPeices[j].x 
                    && _playerPeices[i].y == _playerPeices[j].y
                    && _playerPeices[i].z == _playerPeices[j].z
                )
                || (
                    _playerPeices[i].x == _playerPeices[j].x 
                    && _playerPeices[i].y+1 == _playerPeices[j].y
                    && _playerPeices[i].z == _playerPeices[j].z
                )
                || (
                    _playerPeices[i].x == _playerPeices[j].x
                    && _playerPeices[i].y-1 == _playerPeices[j].y
                    && _playerPeices[i].z == _playerPeices[j].z
                )
                || (
                    _playerPeices[i].x == _playerPeices[j].x
                    && _playerPeices[i].y == _playerPeices[j].y
                    && _playerPeices[i].z+1 == _playerPeices[j].z
                )
                || (
                    _playerPeices[i].x == _playerPeices[j].x
                    && _playerPeices[i].y == _playerPeices[j].y
                    && _playerPeices[i].z-1 == _playerPeices[j].z
                )
            ) {
                int groupOne = playerGroups[i];
                int groupTwo = playerGroups[j];

                for (int k = 0; k < playerGroups.size(); k++) {
                    if (playerGroups[k] == groupTwo) {
                        playerGroups[k] = groupOne;
                        groupCounts[groupOne] += 1;
                        groupCounts[groupTwo] -= 1;
                    }
                }

                for (int k = 0; k < staticGroups.size(); k++) {
                    if (staticGroups[k] == groupTwo) {
                        staticGroups[k] = groupOne;
                        groupCounts[groupOne] += 1;
                        groupCounts[groupTwo] -= 1;
                    }
                }
            }
        }
        for (int j = i+1; j < _static.size(); j++)
        {
            if (
                (
                    _playerPeices[i].x+1 == _static[j].x
                    && _playerPeices[i].y == _static[j].y
                    && _playerPeices[i].z == _static[j].z
                )
                || (
                    _playerPeices[i].x-1 == _static[j].x 
                    && _playerPeices[i].y == _static[j].y
                    && _playerPeices[i].z == _static[j].z
                )
                || (
                    _playerPeices[i].x == _static[j].x 
                    && _playerPeices[i].y+1 == _static[j].y
                    && _playerPeices[i].z == _static[j].z
                )
                || (
                    _playerPeices[i].x == _static[j].x
                    && _playerPeices[i].y-1 == _static[j].y
                    && _playerPeices[i].z == _static[j].z
                )
                || (
                    _playerPeices[i].x == _static[j].x
                    && _playerPeices[i].y == _static[j].y
                    && _playerPeices[i].z+1 == _static[j].z
                )
                || (
                    _playerPeices[i].x == _static[j].x
                    && _playerPeices[i].y == _static[j].y
                    && _playerPeices[i].z-1 == _static[j].z
                )
            ) {
                int groupOne = playerGroups[i];
                int groupTwo = staticGroups[j];

                for (int k = 0; k < playerGroups.size(); k++) {
                    if (playerGroups[k] == groupTwo) {
                        playerGroups[k] = groupOne;
                        groupCounts[groupOne] += 1;
                        groupCounts[groupTwo] -= 1;
                    }
                }

                for (int k = 0; k < staticGroups.size(); k++) {
                    if (staticGroups[k] == groupTwo) {
                        staticGroups[k] = groupOne;
                        groupCounts[groupOne] += 1;
                        groupCounts[groupTwo] -= 1;
                    }
                }
            }
        }
    }
    for (int i = 0; i < _static.size(); i++) {
        for (int j = i+1; j < _playerPeices.size(); j++)
        {
            if (
                (
                    _static[i].x+1 == _playerPeices[j].x
                    && _static[i].y == _playerPeices[j].y
                    && _static[i].z == _playerPeices[j].z
                )
                || (
                    _static[i].x-1 == _playerPeices[j].x 
                    && _static[i].y == _playerPeices[j].y
                    && _static[i].z == _playerPeices[j].z
                )
                || (
                    _static[i].x == _playerPeices[j].x 
                    && _static[i].y+1 == _playerPeices[j].y
                    && _static[i].z == _playerPeices[j].z
                )
                || (
                    _static[i].x == _playerPeices[j].x
                    && _static[i].y-1 == _playerPeices[j].y
                    && _static[i].z == _playerPeices[j].z
                )
                || (
                    _static[i].x == _playerPeices[j].x
                    && _static[i].y == _playerPeices[j].y
                    && _static[i].z+1 == _playerPeices[j].z
                )
                || (
                    _static[i].x == _playerPeices[j].x
                    && _static[i].y == _playerPeices[j].y
                    && _static[i].z-1 == _playerPeices[j].z
                )
            ) {
                int groupOne = staticGroups[i];
                int groupTwo = playerGroups[j];

                for (int k = 0; k < playerGroups.size(); k++) {
                    if (playerGroups[k] == groupTwo) {
                        playerGroups[k] = groupOne;
                        groupCounts[groupOne] += 1;
                        groupCounts[groupTwo] -= 1;
                    }
                }

                for (int k = 0; k < staticGroups.size(); k++) {
                    if (staticGroups[k] == groupTwo) {
                        staticGroups[k] = groupOne;
                        groupCounts[groupOne] += 1;
                        groupCounts[groupTwo] -= 1;
                    }
                }
            }
        }
        for (int j = i+1; j < _static.size(); j++)
        {
            if (
                (
                    _static[i].x+1 == _static[j].x
                    && _static[i].y == _static[j].y
                    && _static[i].z == _static[j].z
                )
                || (
                    _static[i].x-1 == _static[j].x 
                    && _static[i].y == _static[j].y
                    && _static[i].z == _static[j].z
                )
                || (
                    _static[i].x == _static[j].x 
                    && _static[i].y+1 == _static[j].y
                    && _static[i].z == _static[j].z
                )
                || (
                    _static[i].x == _static[j].x
                    && _static[i].y-1 == _static[j].y
                    && _static[i].z == _static[j].z
                )
                || (
                    _static[i].x == _static[j].x
                    && _static[i].y == _static[j].y
                    && _static[i].z+1 == _static[j].z
                )
                || (
                    _static[i].x == _static[j].x
                    && _static[i].y == _static[j].y
                    && _static[i].z-1 == _static[j].z
                )
            ) {
                int groupOne = staticGroups[i];
                int groupTwo = staticGroups[j];

                for (int k = 0; k < playerGroups.size(); k++) {
                    if (playerGroups[k] == groupTwo) {
                        playerGroups[k] = groupOne;
                        groupCounts[groupOne] += 1;
                        groupCounts[groupTwo] -= 1;
                    }
                }

                for (int k = 0; k < staticGroups.size(); k++) {
                    if (staticGroups[k] == groupTwo) {
                        staticGroups[k] = groupOne;
                        groupCounts[groupOne] += 1;
                        groupCounts[groupTwo] -= 1;
                    }
                }
            }
        }
    }

    int top = -1;
    int topIndex;
    for (int i = 0; i < groupCounts.size(); i++) {
        if (groupCounts[i] > top) {
            top = groupCounts[i];
            topIndex = i;
        }
    }

    for (int i = 0; i < _playerPeices.size(); i++) {
        if (playerGroups[i] != topIndex) {
            _static.push_back(_playerPeices[i]);
            _playerPeices.erase(_playerPeices.begin() + i);
            playerGroups.erase(playerGroups.begin() + i);
            i -= 1;
        }
    }

    for (int i = 0; i < staticGroups.size(); i++) {
        if (staticGroups[i] == topIndex) {
            _playerPeices.push_back(_static[i]);
            _static.erase(_static.begin() + i);
            staticGroups.erase(staticGroups.begin() + i);
            i -= 1;
        }
    }
}

void Player::attach() {
    for (int i = 0; i < _playerPeices.size(); i++) {
        for (int j = 0; j < _static.size(); j++)
        {
            if (
                (
                    _playerPeices[i].x+1 == _static[j].x
                    && _playerPeices[i].y == _static[j].y
                    && _playerPeices[i].z == _static[j].z
                )
                || (
                    _playerPeices[i].x-1 == _static[j].x 
                    && _playerPeices[i].y == _static[j].y
                    && _playerPeices[i].z == _static[j].z
                )
                || (
                    _playerPeices[i].x == _static[j].x 
                    && _playerPeices[i].y+1 == _static[j].y
                    && _playerPeices[i].z == _static[j].z
                )
                || (
                    _playerPeices[i].x == _static[j].x
                    && _playerPeices[i].y-1 == _static[j].y
                    && _playerPeices[i].z == _static[j].z
                )
                || (
                    _playerPeices[i].x == _static[j].x
                    && _playerPeices[i].y == _static[j].y
                    && _playerPeices[i].z+1 == _static[j].z
                )
                || (
                    _playerPeices[i].x == _static[j].x
                    && _playerPeices[i].y == _static[j].y
                    && _playerPeices[i].z-1 == _static[j].z
                )
            ) {
                _playerPeices.push_back(_static[j]);
                _static.erase(_static.begin() + j);
                j -= 1;
            }
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
        * glm::scale(glm::mat4(1.0f), glm::vec3(GLOBAL::BLOCK_WIDTH, GLOBAL::BLOCK_WIDTH, GLOBAL::BLOCK_WIDTH))
        * glm::translate(
            glm::mat4(1.0f), 
            glm::vec3(
                (-(_floorWidth/2.0f) + peice.x + 0.5f) * (1.0/(GLOBAL::BLOCK_WIDTH)),
                (0.5f + peice.y) * (1.0/(GLOBAL::BLOCK_WIDTH)),
                (-(_floorLength/2.0f) + peice.z + 0.5f) * (1.0/(GLOBAL::BLOCK_WIDTH))
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
        * glm::scale(glm::mat4(1.0f), glm::vec3((GLOBAL::BLOCK_WIDTH), (GLOBAL::BLOCK_WIDTH), (GLOBAL::BLOCK_WIDTH)))
        * glm::translate(
            glm::mat4(1.0f), 
            glm::vec3(
                (-(_floorWidth/2.0f) + peice.x + 0.5f) * (1.0/(GLOBAL::BLOCK_WIDTH)),
                (0.5f + peice.y - peice[3]*peice[3]*0.005) * (1.0/(GLOBAL::BLOCK_WIDTH)),
                (-(_floorLength/2.0f) + peice.z + 0.5f) * (1.0/(GLOBAL::BLOCK_WIDTH))
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
    for (glm::vec3 peice: _static) {
        _transformMatrix = viewProjectionMatrix
        * glm::scale(glm::mat4(1.0f), glm::vec3((GLOBAL::BLOCK_WIDTH), (GLOBAL::BLOCK_WIDTH), (GLOBAL::BLOCK_WIDTH)))
        * glm::translate(
            glm::mat4(1.0f), 
            glm::vec3(
                (-(_floorWidth/2.0f) + peice.x + 0.5f) * (1.0/(GLOBAL::BLOCK_WIDTH)),
                (0.5f + peice.y) * (1.0/(GLOBAL::BLOCK_WIDTH)),
                (-(_floorLength/2.0f) + peice.z + 0.5f) * (1.0/(GLOBAL::BLOCK_WIDTH))
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
    for (glm::vec3 peice: _done) {
        _transformMatrix = viewProjectionMatrix
        * glm::scale(glm::mat4(1.0f), glm::vec3((GLOBAL::BLOCK_WIDTH), (GLOBAL::BLOCK_WIDTH), (GLOBAL::BLOCK_WIDTH)))
        * glm::translate(
            glm::mat4(1.0f), 
            glm::vec3(
                (-(_floorWidth/2.0f) + peice.x + 0.5f) * (1.0/(GLOBAL::BLOCK_WIDTH)),
                (0.5f + peice.y) * (1.0/(GLOBAL::BLOCK_WIDTH)),
                (-(_floorLength/2.0f) + peice.z + 0.5f) * (1.0/(GLOBAL::BLOCK_WIDTH))
            )
        );
        glUniformMatrix4fv(
            _shader->getUniformLocation("transformMatrix"), 
            1, 
            GL_FALSE, 
            glm::value_ptr(_transformMatrix)
        );
        glBindVertexArray(_doneVertexArrayObject);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glBindVertexArray(_lineVertexArrayObject);
        glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);
    }
}

glm::vec3 Player::getCameraPos() {
    return _cameraPos;
}

glm::vec2 Player::getCameraDistance() {
    return _cameraDistance;
}