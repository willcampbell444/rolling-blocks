#include <player.h>

Player::Player(Renderer* renderer) {
    _renderer = renderer;
}

void Player::create(int x, int y, unsigned char* map, std::vector<glm::vec3> startPosition) {
    _floorWidth = x;
    _floorLength = y;

    _moveCount = 0;
    
    _heightMap.create(_floorWidth, _floorLength);

    _startPosition = startPosition;

    _static.clear();
    _falling.clear();
    _done.clear();
    _endTimer = 0;

    _rotationAxis = glm::vec3(0, 0, 1);

    _playerPeices = startPosition;
    _newPeices = _playerPeices;
    gravity();
    onWinTile(map);

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
                0
            ));
            _playerPeices.erase(_playerPeices.begin() + i);
            i -= 1;
        }
    }

    attach();
    sever();

    for (int i = 0; i < _playerPeices.size(); i++) {
        if (playerGroups[i] != _groups[_group]) {
            _static.push_back(_playerPeices[i]);
            staticGroups.push_back(playerGroups[i]);
            _playerPeices.erase(_playerPeices.begin() + i);
            playerGroups.erase(playerGroups.begin() + i);
            i -= 1;
        }
    }

    for (int i = 0; i < _playerPeices.size(); i++) {
        if (map[(int)(_playerPeices[i].x*_floorLength + _playerPeices[i].z)] == 2) {
            _done.push_back(glm::vec4(_playerPeices[i].x, _playerPeices[i].y, _playerPeices[i].z, 0));
            _playerPeices.erase(_playerPeices.begin() + i);
            i -= 1;
        }
    }

    setMinMax();

    _cameraPos = glm::vec3(
        (_minX+_maxX)/2.0f,
        (_minY+_maxY+1)/2.0f,
        (_minZ+_maxZ)/2.0f
    );

    if (_maxX - _minX > _maxZ - _minZ) {
        _cameraDistance.x = _maxX - _minX + 5;
    } else {
        _cameraDistance.x = _maxZ - _minZ + 5;
    }
    _cameraDistance.y = _maxY - _minY + 3;

    _group = 0;

    _isBeginning = true;

    _newCameraPos = _cameraPos;
    _newCameraDistance = _cameraDistance;
    _oldCameraPos = _cameraPos;
    _oldCameraPos.y += GLOBAL::FALL_HEIGHT*_cameraDistance.y;
    _oldCameraDistance = _cameraDistance;

    _finished = false;
    _isEnding = false;
    _wait = false;
    _won = false;
    _timeSinceTransition = 0;
    _isRestartTransition = false;

    update(map, 0);
}

// true if the game is over
bool Player::win() {
    if (_won && !_isEnding) {
        _isTransition = false;
        _isCameraTransition = false;
        _timeSinceTransition = 0;
        _wait = true;
        _isEnding = true;
        _newCameraPos = _cameraPos;
        _newCameraPos.y = GLOBAL::FALL_HEIGHT*_cameraDistance.y;
        _newCameraDistance = _cameraDistance;
        _oldCameraPos = _cameraPos;
        _oldCameraDistance = _cameraDistance;
    }
    if (_finished) {
        return true;
    }
    return false;
}

int Player::getMoveCount() {
    return _moveCount;
}

void Player::restart() {
    if (!_isTransition && !_isCameraTransition && !_isBeginning && !_isEnding && !_isRestartTransition) {
        _isRestartTransition = true;
        _newCameraPos = _cameraPos;
        _newCameraPos.y = GLOBAL::FALL_HEIGHT*_cameraDistance.y;
        _newCameraDistance = _cameraDistance;
        _oldCameraPos = _cameraPos;
        _oldCameraDistance = _cameraDistance;
    }
}

void Player::end() {
    if (!_isTransition && !_isCameraTransition && !_isBeginning && !_isEnding && !_wait && !_isRestartTransition) {
        _isEnding = true;
        _newCameraPos = _cameraPos;
        _newCameraPos.y = GLOBAL::FALL_HEIGHT*_cameraDistance.y;
        _newCameraDistance = _cameraDistance;
        _oldCameraPos = _cameraPos;
        _oldCameraDistance = _cameraDistance;
    }
}

bool Player::getWinStatus() {
    return _won;
}

void Player::checkVictory(unsigned char* map) {
    bool occupied;
    bool success = true;
    for (int i = 0; i < _floorLength*_floorWidth; i++) {
        if (map[i] == 2) {
            occupied = false;
            for (glm::vec4 peice: _done) {
                if (peice.x == i/_floorLength && peice.z == i % _floorLength) {
                    occupied = true;
                }
            }
            if (!occupied) {
                success = false;
                break;
            }
        }
    }
    if (success) {
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
    if (!_isTransition && !_isCameraTransition && !_isBeginning && !_isEnding && !_wait && !_isRestartTransition) {
        fillHeightMap();
        _isTransition = true;
        _angle = 90.0f;
        _rotationAxis = glm::vec3(z, 0, x);
        _timeSinceTransition = 0;
        _oldCameraPos = _cameraPos;
        _oldCameraDistance = _cameraDistance;
        _newPeices = _playerPeices;
        _moveCount += 1;

        setMinMax();

        if (x == 1) {
            for (int i = 0; i < _newPeices.size(); i++) {
                _newPeices[i].x = _maxX+_playerPeices[i].y+1;
                _newPeices[i].y = _maxX-_playerPeices[i].x;
            }
            _angleSign = 1;
            _rotationAxisPosition = glm::vec3(_maxX+1-0.5f, 0, 0);
        } else if (x == -1) {
            for (int i = 0; i < _newPeices.size(); i++) {
                _newPeices[i].x = _minX-_playerPeices[i].y-1;
                _newPeices[i].y = _playerPeices[i].x-_minX;
            }
            _angleSign = 1;
            _rotationAxisPosition = glm::vec3(_minX-0.5f, 0, 0);
        }
        if (z == 1) {
            for (int i = 0; i < _newPeices.size(); i++) {
                _newPeices[i].z = _maxZ+_playerPeices[i].y+1;
                _newPeices[i].y = _maxZ-_playerPeices[i].z;
            }
            _angleSign = -1;
            _rotationAxisPosition = glm::vec3(0, 0, _maxZ+1-0.5f);
        } else if (z == -1) {
            for (int i = 0; i < _newPeices.size(); i++) {
                _newPeices[i].z = _minZ-_playerPeices[i].y-1;
                _newPeices[i].y = _playerPeices[i].z-_minZ;
            }
            _angleSign = -1;
            _rotationAxisPosition = glm::vec3(0, 0, _minZ-0.5f);
        }

        _oldPeices = _playerPeices;
        _playerPeices = _newPeices;

        onBlock(x, z);
        gravity();

        _oldPeices = _playerPeices;

        onWinTile(map);
        setMinMax();

        _newCameraPos = glm::vec3(
            (_minX+_maxX)/2.0f,
            (_minY+_maxY+1)/2.0f,
            (_minZ+_maxZ)/2.0f
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

void Player::update(unsigned char* map, GLfloat deltaTime) {
    if (
        _wait
        || _isTransition
        || _isCameraTransition
        || _isBeginning
        || _isEnding
        || _isRestartTransition
    ) {
        _timeSinceTransition += deltaTime;
        float mu = _timeSinceTransition/GLOBAL::TRANSITION_LENGTH;

        if (_wait) {
            if (_timeSinceTransition >= GLOBAL::TRANSITION_LENGTH) {
                _wait = false;
                _timeSinceTransition = 0;
            }
        } else if (_isTransition) {
            mu = (mu * mu);
            _angle = 90.0f*(1-mu);
            for (int i = 0; i < _playerPeices.size(); i++) {
                _playerPeices[i].y = _oldPeices[i].y*(1-mu) + _newPeices[i].y*mu;
                _playerPeices[i].z = _oldPeices[i].z*(1-mu) + _newPeices[i].z*mu;
                _playerPeices[i].x = _oldPeices[i].x*(1-mu) + _newPeices[i].x*mu;
            }
            mu = _timeSinceTransition/GLOBAL::TRANSITION_LENGTH;
            mu = (mu * mu * (3 - 2 * (mu)));
            _cameraPos = _oldCameraPos*(1.0f-mu) + _newCameraPos*mu;
            _cameraDistance = _oldCameraDistance*(1.0f-mu) + _newCameraDistance*mu;
            if (_timeSinceTransition >= GLOBAL::TRANSITION_LENGTH) {
                _isTransition = false;
                _timeSinceTransition = 0;
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
                            0
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
                    (_minX+_maxX)/2.0f,
                    (_minY+_maxY+1)/2.0f,
                    (_minZ+_maxZ)/2.0f
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

                checkVictory(map);
            }
        } else if (_isCameraTransition) {
            mu = (mu * mu * (3 - 2 * (mu)));
            _cameraPos = _oldCameraPos*(1.0f-mu) + _newCameraPos*mu;
            _cameraDistance = _oldCameraDistance*(1.0f-mu) + _newCameraDistance*mu;
            if (_timeSinceTransition >= GLOBAL::TRANSITION_LENGTH) {
                _isCameraTransition = false;
                _oldCameraDistance = _newCameraDistance;
                _oldCameraPos = _newCameraPos;
                _timeSinceTransition = 0;
            }
        } else if (_isBeginning) {
            mu = (mu * mu * (3 - 2 * (mu)));
            _cameraPos = _oldCameraPos*(1.0f-mu) + _newCameraPos*mu;
            _cameraDistance = _oldCameraDistance*(1.0f-mu) + _newCameraDistance*mu;
            if (_timeSinceTransition >= GLOBAL::TRANSITION_LENGTH) {
                _isBeginning = false;
                _oldCameraDistance = _newCameraDistance;
                _oldCameraPos = _newCameraPos;
                _cameraDistance = _newCameraDistance;
                _cameraPos = _newCameraPos;
                _timeSinceTransition = 0;
            }
        } else if (_isEnding) {
            mu = (mu * mu * (3 - 2 * (mu)));
            _cameraPos = _oldCameraPos*(1.0f-mu) + _newCameraPos*mu;
            _cameraDistance = _oldCameraDistance*(1.0f-mu) + _newCameraDistance*mu;
            if (_timeSinceTransition >= GLOBAL::TRANSITION_LENGTH) {
                _isEnding = false;
                _finished = true;
                _oldCameraDistance = _newCameraDistance;
                _oldCameraPos = _newCameraPos;
                _timeSinceTransition = 0;
            }
        } else if (_isRestartTransition) {
            mu = (mu * mu * (3 - 2 * (mu)));
            _cameraPos = _oldCameraPos*(1.0f-mu) + _newCameraPos*mu;
            _cameraDistance = _oldCameraDistance*(1.0f-mu) + _newCameraDistance*mu;
            if (_timeSinceTransition >= GLOBAL::TRANSITION_LENGTH) {
                create(_floorWidth, _floorLength, map, _startPosition);
            }
        }
    }
    for (int i = 0; i < _falling.size(); i++) {
        _falling[i][3] += 60*deltaTime;
        if (_falling[i][3] > 1000) {
            _falling.erase(_falling.begin() + i);
        }
    }
    if (!_won) {
        for (int i = 0; i < _done.size(); i++) {
            _done[i][3] += deltaTime;
            if (_done[i].y - (_done[i].w*_done[i].w) < -5) {
                _done.erase(_done.begin() + i);
            }
        }
    }
    if (_playerPeices.size() == 0 && !_won && !_isRestartTransition) {
        restart();
        _isCameraTransition = false;
        _wait = true;
    }
}

void Player::changeGroup(int direction) {
    if (!_isTransition && !_isCameraTransition && !_isBeginning && !_isEnding && !_wait && !_isRestartTransition){
        _group += direction;
        if (_group < 0) {
            _group = _groups.size() - 1;
        } else if (_group >= _groups.size()) {
            _group = 0;
        }

        for (int i = 0; i < _playerPeices.size(); i++) {
            if (playerGroups[i] != _groups[_group]) {
                _static.push_back(_playerPeices[i]);
                staticGroups.push_back(playerGroups[i]);
                _playerPeices.erase(_playerPeices.begin() + i);
                playerGroups.erase(playerGroups.begin() + i);
                i -= 1;
            }
        }

        for (int i = 0; i < staticGroups.size(); i++) {
            if (staticGroups[i] == _groups[_group]) {
                _playerPeices.push_back(_static[i]);
                playerGroups.push_back(staticGroups[i]);
                _static.erase(_static.begin() + i);
                staticGroups.erase(staticGroups.begin() + i);
                i -= 1;
            }
        }

        if (direction != 0) {
            _isCameraTransition = true;

            _oldCameraPos = _cameraPos;
            _oldCameraDistance = _cameraDistance;

            setMinMax();

            _newCameraPos = glm::vec3(
                (_minX+_maxX)/2.0f,
                (_minY+_maxY+1)/2.0f,
                (_minZ+_maxZ)/2.0f
            );

            if (_maxX - _minX > _maxZ - _minZ) {
                _newCameraDistance.x = _maxX - _minX + 5;
            } else {
                _newCameraDistance.x = _maxZ - _minZ + 5;
            }
            _newCameraDistance.y = _maxY - _minY + 3;
        }
    }
}

void Player::sever() {
    playerGroups.clear();
    staticGroups.clear();
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

    _groups.clear();
    for (int i = 0; i < groupCounts.size(); i++) {
        if (groupCounts[i] > 0) {
            _groups.push_back(i);
        }
    }

    _group = 0;
    changeGroup(0);
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
    for (glm::vec3 peice: _playerPeices) {
        _renderer->drawRotatedBox(
            viewProjectionMatrix, 
            peice.x, 
            peice.y, 
            peice.z, 
            _angleSign*_angle, 
            _rotationAxisPosition, 
            _rotationAxis, 
            GLOBAL::PLAYER_COLOR
        );
    }
    for (glm::vec4 peice: _falling) {
        _renderer->drawBox(viewProjectionMatrix, peice.x, peice.y - peice[3]*peice[3]*0.005, peice.z, GLOBAL::PLAYER_COLOR);
    }
    for (glm::vec3 peice: _static) {
        _renderer->drawBox(viewProjectionMatrix, peice.x, peice.y, peice.z, GLOBAL::PLAYER_COLOR);
    }
    for (glm::vec4 peice: _done) {
        if (_won) {
            _renderer->drawBox(viewProjectionMatrix, peice.x, peice.y, peice.z, GLOBAL::WON_COLOR);
        } else {
            _renderer->drawBox(viewProjectionMatrix, peice.x, peice.y-(peice.w*peice.x), peice.z, GLOBAL::VICTORY_COLOR);
        }
    }
    _renderer->drawTextTop("MOVE "+std::to_string(_moveCount), 20, 55, 1, GLOBAL::TEXT_COLOR);
}

glm::vec3 Player::getCameraPos() {
    return _cameraPos;
}

glm::vec2 Player::getCameraDistance() {
    return _cameraDistance;
}