#include <menu.h>

// LETTERS: (each bit is a block, these are the positions of the bits)
// 0  1  2  3  4
// 5  6  7  8  9
// 10 11 12 13 14
// 15 16 17 18 19
// 20 21 22 23 24

Menu::Menu(Renderer* renderer) {
    _renderer = renderer;

    // http://www.dafont.com/visitor.font
    _chars['A'] = loadLetter(std::move((bool[25]){
        1, 1, 1, 1, 1,
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 1, 
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1
    }));
    _chars['B'] = loadLetter(std::move((bool[25]){
        1, 1, 1, 1, 0,
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 1, 
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 0
    }));
    _chars['C'] = loadLetter(std::move((bool[25]){
        1, 1, 1, 1, 1,
        1, 0, 0, 0, 0,
        1, 0, 0, 0, 0, 
        1, 0, 0, 0, 0,
        1, 1, 1, 1, 1
    }));
    _chars['D'] = loadLetter(std::move((bool[25]){
        1, 1, 1, 1, 0,
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1, 
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 0
    }));
    _chars['E'] = loadLetter(std::move((bool[25]){
        1, 1, 1, 1, 1,
        1, 0, 0, 0, 0,
        1, 1, 1, 0, 0, 
        1, 0, 0, 0, 0,
        1, 1, 1, 1, 1
    }));
    _chars['F'] = loadLetter(std::move((bool[25]){
        1, 1, 1, 1, 1,
        1, 0, 0, 0, 0,
        1, 1, 1, 0, 0, 
        1, 0, 0, 0, 0,
        1, 0, 0, 0, 0
    }));
    _chars['G'] = loadLetter(std::move((bool[25]){
        1, 1, 1, 1, 1,
        1, 0, 0, 0, 0,
        1, 0, 1, 1, 1, 
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 1
    }));
    _chars['H'] = loadLetter(std::move((bool[25]){
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 1, 
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1
    }));
    _chars['I'] = loadLetter(std::move((bool[25]){
        1, 1, 1, 1, 1,
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0, 
        0, 0, 1, 0, 0,
        1, 1, 1, 1, 1
    }));
    _chars['J'] = loadLetter(std::move((bool[25]){
        0, 0, 0, 0, 1,
        0, 0, 0, 0, 1,
        0, 0, 0, 0, 1, 
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 1
    }));
    _chars['K'] = loadLetter(std::move((bool[25]){
        1, 0, 0, 0, 1,
        1, 0, 0, 1, 0,
        1, 1, 1, 0, 0, 
        1, 0, 0, 1, 0,
        1, 0, 0, 0, 1
    }));
    _chars['L'] = loadLetter(std::move((bool[25]){
        1, 0, 0, 0, 0,
        1, 0, 0, 0, 0,
        1, 0, 0, 0, 0, 
        1, 0, 0, 0, 0,
        1, 1, 1, 1, 1
    }));
    _chars['M'] = loadLetter(std::move((bool[25]){
        1, 0, 0, 0, 1,
        1, 1, 0, 1, 1,
        1, 0, 1, 0, 1, 
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1
    }));
    _chars['N'] = loadLetter(std::move((bool[25]){
        1, 0, 0, 0, 1,
        1, 1, 0, 0, 1,
        1, 0, 1, 0, 1, 
        1, 0, 0, 1, 1,
        1, 0, 0, 0, 1
    }));
    _chars['O'] = loadLetter(std::move((bool[25]){
        1, 1, 1, 1, 1,
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1, 
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 1
    }));
    _chars['P'] = loadLetter(std::move((bool[25]){
        1, 1, 1, 1, 0,
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 1, 
        1, 0, 0, 0, 0,
        1, 0, 0, 0, 0
    }));
    _chars['Q'] = loadLetter(std::move((bool[25]){
        1, 1, 1, 1, 1,
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1, 
        1, 0, 1, 0, 1,
        1, 1, 1, 1, 1
    }));
    _chars['R'] = loadLetter(std::move((bool[25]){
        1, 1, 1, 1, 0,
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 1, 
        1, 0, 0, 1, 0,
        1, 0, 0, 0, 1
    }));
    _chars['S'] = loadLetter(std::move((bool[25]){
        1, 1, 1, 1, 1,
        1, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 
        0, 0, 0, 0, 1,
        1, 1, 1, 1, 1
    }));
    _chars['T'] = loadLetter(std::move((bool[25]){
        1, 1, 1, 1, 1,
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0, 
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0
    }));
    _chars['U'] = loadLetter(std::move((bool[25]){
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1, 
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 1
    }));
    _chars['V'] = loadLetter(std::move((bool[25]){
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1, 
        0, 1, 0, 1, 0,
        0, 0, 1, 0, 0
    }));
    _chars['W'] = loadLetter(std::move((bool[25]){
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1,
        1, 0, 1, 0, 1, 
        1, 1, 0, 1, 1,
        1, 0, 0, 0, 1
    }));
    _chars['X'] = loadLetter(std::move((bool[25]){
        1, 0, 0, 0, 1,
        0, 1, 0, 1, 0,
        0, 0, 1, 0, 0, 
        0, 1, 0, 1, 0,
        1, 0, 0, 0, 1
    }));
    _chars['Y'] = loadLetter(std::move((bool[25]){
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 1, 
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0
    }));
    _chars['Z'] = loadLetter(std::move((bool[25]){
        1, 1, 1, 1, 1,
        0, 0, 0, 1, 0,
        0, 0, 1, 0, 0, 
        0, 1, 0, 0, 0,
        1, 1, 1, 1, 1
    }));
    _chars['0'] = loadLetter(std::move((bool[25]){
        1, 1, 1, 1, 1,
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1, 
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 1
    }));
    _chars['1'] = loadLetter(std::move((bool[25]){
        0, 1, 1, 0, 0,
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0, 
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0
    }));
    _chars['2'] = loadLetter(std::move((bool[25]){
        1, 1, 1, 1, 1,
        0, 0, 0, 0, 1,
        1, 1, 1, 1, 1, 
        1, 0, 0, 0, 0,
        1, 1, 1, 1, 1
    }));
    _chars['3'] = loadLetter(std::move((bool[25]){
        1, 1, 1, 1, 1,
        0, 0, 0, 0, 1,
        0, 0, 1, 1, 1, 
        0, 0, 0, 0, 1,
        1, 1, 1, 1, 1
    }));
    _chars['4'] = loadLetter(std::move((bool[25]){
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 1, 
        0, 0, 0, 0, 1,
        0, 0, 0, 0, 1
    }));
    _chars['5'] = loadLetter(std::move((bool[25]){
        1, 1, 1, 1, 1,
        1, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 
        0, 0, 0, 0, 1,
        1, 1, 1, 1, 1
    }));
    _chars['6'] = loadLetter(std::move((bool[25]){
        1, 1, 1, 1, 1,
        1, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 1
    }));
    _chars['7'] = loadLetter(std::move((bool[25]){
        1, 1, 1, 1, 1,
        0, 0, 0, 0, 1,
        0, 0, 0, 0, 1, 
        0, 0, 0, 0, 1,
        0, 0, 0, 0, 1
    }));
    _chars['8'] = loadLetter(std::move((bool[25]){
        1, 1, 1, 1, 1,
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 1, 
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 1
    }));
    _chars['9'] = loadLetter(std::move((bool[25]){
        1, 1, 1, 1, 1,
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 1, 
        0, 0, 0, 0, 1,
        0, 0, 0, 0, 1
    }));
    _chars[' '] = loadLetter(std::move((bool[25]){
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0
    }));

    //SET UP VAOs

    float vertices[36*6] = {
        -0.5,  0.5f,  -0.5, 0.0f, 1.0f, 0.0f,
        -0.5,  0.5f,   0.5, 0.0f, 1.0f, 0.0f,
         0.5,  0.5f,   0.5, 0.0f, 1.0f, 0.0f,
         0.5,  0.5f,   0.5, 0.0f, 1.0f, 0.0f,
         0.5,  0.5f,  -0.5, 0.0f, 1.0f, 0.0f,
        -0.5,  0.5f,  -0.5, 0.0f, 1.0f, 0.0f,

        -0.5, -0.5f,  -0.5, 0.0f, -1.0f, 0.0f,
        -0.5, -0.5f,   0.5, 0.0f, -1.0f, 0.0f,
         0.5, -0.5f,   0.5, 0.0f, -1.0f, 0.0f,
         0.5, -0.5f,   0.5, 0.0f, -1.0f, 0.0f,
         0.5, -0.5f,  -0.5, 0.0f, -1.0f, 0.0f,
        -0.5, -0.5f,  -0.5, 0.0f, -1.0f, 0.0f,

        -0.5, -0.5f,  -0.5, -1.0f, 0.0f, 0.0f,
        -0.5, -0.5f,   0.5, -1.0f, 0.0f, 0.0f,
        -0.5,  0.5f,   0.5, -1.0f, 0.0f, 0.0f,
        -0.5,  0.5f,   0.5, -1.0f, 0.0f, 0.0f,
        -0.5,  0.5f,  -0.5, -1.0f, 0.0f, 0.0f,
        -0.5, -0.5f,  -0.5, -1.0f, 0.0f, 0.0f,

         0.5, -0.5f,   0.5, 1.0f, 0.0f, 0.0f,
         0.5, -0.5f,  -0.5, 1.0f, 0.0f, 0.0f,
         0.5,  0.5f,  -0.5, 1.0f, 0.0f, 0.0f,
         0.5,  0.5f,  -0.5, 1.0f, 0.0f, 0.0f,
         0.5,  0.5f,   0.5, 1.0f, 0.0f, 0.0f,
         0.5, -0.5f,   0.5, 1.0f, 0.0f, 0.0f,

        -0.5, -0.5f,  -0.5, 0.0f, 0.0f, -1.0f,
        -0.5,  0.5f,  -0.5, 0.0f, 0.0f, -1.0f,
         0.5,  0.5f,  -0.5, 0.0f, 0.0f, -1.0f,
         0.5,  0.5f,  -0.5, 0.0f, 0.0f, -1.0f,
         0.5, -0.5f,  -0.5, 0.0f, 0.0f, -1.0f,
        -0.5, -0.5f,  -0.5, 0.0f, 0.0f, -1.0f,

        -0.5, -0.5f,   0.5, 0.0f, 0.0f, 1.0f,
        -0.5,  0.5f,   0.5, 0.0f, 0.0f, 1.0f,
         0.5,  0.5f,   0.5, 0.0f, 0.0f, 1.0f,
         0.5,  0.5f,   0.5, 0.0f, 0.0f, 1.0f,
         0.5, -0.5f,   0.5, 0.0f, 0.0f, 1.0f,
        -0.5, -0.5f,   0.5, 0.0f, 0.0f, 1.0f
    };

    float lineVertecies[8*3*3] = {
        -0.5,  0.5f,  -0.5,
        -0.5,  0.5f,   0.5,
        -0.5,  0.5f,   0.5,
         0.5,  0.5f,   0.5,
         0.5,  0.5f,   0.5,
         0.5,  0.5f,  -0.5,
         0.5,  0.5f,  -0.5,
        -0.5,  0.5f,  -0.5,

        -0.5, -0.5f,  -0.5,
        -0.5, -0.5f,   0.5,
        -0.5, -0.5f,   0.5,
         0.5, -0.5f,   0.5,
         0.5, -0.5f,   0.5,
         0.5, -0.5f,  -0.5,
         0.5, -0.5f,  -0.5,
        -0.5, -0.5f,  -0.5,

        -0.5,  0.5f,  -0.5,
        -0.5, -0.5f,  -0.5,
        -0.5,  0.5f,   0.5,
        -0.5, -0.5f,   0.5,
         0.5,  0.5f,   0.5,
         0.5, -0.5f,   0.5,
         0.5,  0.5f,  -0.5,
         0.5, -0.5f,  -0.5
    };
}

void Menu::move(int direction) {
    if (!_isCameraTransition && !_isTransition && !_isEndTransition && !_isBeginning) {
        _currentPeice += direction;
        if (_currentPeice < 0) {
            _currentPeice = _options.size() - 1;
        } else if (_currentPeice >= _options.size()) {
            _currentPeice = 0;
        }

        _oldCameraPos = _cameraPos;
        _oldCameraDistance = _cameraDistance;
        setCamera();
        _newCameraPos = _cameraPos;
        _newCameraDistance = _cameraDistance;

        _isCameraTransition = true;
    }
}

bool Menu::isStill() {
    return (!_isCameraTransition && !_isTransition && !_isEndTransition && !_isBeginning);
}

void Menu::end() {
    _oldCameraDistance = _cameraDistance;
    _oldCameraPos = _cameraPos;
    _newCameraPos = _cameraPos;
    _newCameraDistance = _cameraDistance;
    _newCameraPos.y += GLOBAL::FALL_HEIGHT*_cameraDistance.y;
    _isEndTransition = true;
    _forcedEnd = true;
}

void Menu::select() {
    if (!_isCameraTransition && !_isTransition && !_isEndTransition && !_isBeginning) {
        _isTransition = true;

        _oldCameraPos = _cameraPos;
        _oldCameraDistance = _cameraDistance;
        setCamera();
        _cameraPos.x = 2.5f;
        _cameraPos.y = 0;
        _newCameraPos = _cameraPos;
        _newCameraDistance = _cameraDistance;
    }
}

void Menu::update(GLfloat deltaTime) {
    if (
        _wait
        || _isTransition
        || _isCameraTransition
        || _isEndTransition
        || _isBeginning
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
            _height = mu*(-GLOBAL::GAP*4);
            
            mu = _timeSinceTransition/GLOBAL::TRANSITION_LENGTH;
            mu = (mu * mu * (3 - 2 * (mu)));
            _cameraPos = _oldCameraPos*(1.0f-mu) + _newCameraPos*mu;
            _cameraDistance = _oldCameraDistance*(1.0f-mu) + _newCameraDistance*mu;

            if (_timeSinceTransition >= GLOBAL::TRANSITION_LENGTH) {
                _isTransition = false;
                _wait = true;
                _isEndTransition = true;
                _oldCameraDistance = _newCameraDistance;
                _oldCameraPos = _newCameraPos;
                _newCameraPos.y += -GLOBAL::FALL_HEIGHT*_cameraDistance.y;
                _timeSinceTransition = 0;
            }
        } else if (_isCameraTransition) {
            mu = (mu * mu * (3 - 2 * (mu)));
            _cameraPos = _oldCameraPos*(1.0f-mu) + _newCameraPos*mu;
            _cameraDistance = _oldCameraDistance*(1.0f-mu) + _newCameraDistance*mu;
            if (_timeSinceTransition >= GLOBAL::TRANSITION_LENGTH) {
                _isCameraTransition = false;
                _oldCameraDistance = _newCameraDistance;
                _oldCameraPos = _newCameraPos;
                _cameraDistance = _newCameraDistance;
                _cameraPos = _newCameraPos;
                _timeSinceTransition = 0;
            }
        } else if (_isEndTransition) {
            mu = (mu * mu * (3 - 2 * (mu)));
            _cameraPos = _oldCameraPos*(1.0f-mu) + _newCameraPos*mu;
            _cameraDistance = _oldCameraDistance*(1.0f-mu) + _newCameraDistance*mu;
            if (_timeSinceTransition >= GLOBAL::TRANSITION_LENGTH) {
                _isCameraTransition = false;
                _done = true;
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
        }
    }
}

int Menu::result() {
    if (_done) {
        if (_forcedEnd) {
            return -2;
        }
        return _currentPeice;
    }
    return -1;
}

void Menu::setOptions(std::vector<const char*> options, int dir) {
    _options.clear();
    _done = false;
    _isBeginning = true;
    _isEndTransition = false;
    _isCameraTransition = false;
    _isTransition = false;
    _wait = false;
    _forcedEnd = false;
    _timeSinceTransition = 0;
    _currentPeice = 0;
    _angle = 90.0f;
    _height = 0;

    for (int n = 0; n < options.size(); n++) {
        std::vector<unsigned int> v;
        _options.push_back(v);
        for (int c = 0; c < std::string(options[n]).length(); c++) {
            _options[n].push_back(_chars[options[n][c]]);
        }
    }

    setCamera();
    _newCameraPos = _cameraPos;
    _newCameraDistance = _cameraDistance;
    _oldCameraPos = _cameraPos;
    _oldCameraPos.y += GLOBAL::FALL_HEIGHT*_cameraDistance.y*dir;
    _oldCameraDistance = _cameraDistance;

    update(0);
}

unsigned int Menu::loadLetter(bool bits[25]) {
    unsigned int letter = 0;
    for (int i = 0; i < 25; i++) {
        letter += bits[i] << i;
    }
    return letter;
}

void Menu::draw(glm::mat4 viewProjectionMatrix) {
    int count = -1;
    for (int m = 0; m < _options.size(); m++) {
        for (int n = 0; n < _options[m].size(); n++) {
            int letter = _options[m][n];
            for (int i = 0; i < 25; i++) {
                if (letter & (unsigned int)(1 << i)) {
                    if (m == _currentPeice) {
                        if (!_isEndTransition || _forcedEnd) {
                            _renderer->drawRotatedBox(viewProjectionMatrix, 5 - (int)(i/5), _height, i % 5 + count + 1.0f, _angle, glm::vec3(0.5, 0, 0), glm::vec3(0, 0, 1), GLOBAL::PLAYER_COLOR);
                        } else {
                            _renderer->drawBox(viewProjectionMatrix, 5 - (int)(i/5), _height, i % 5 + count + 1.0f, GLOBAL::VICTORY_COLOR);
                        }
                    } else {
                        _renderer->drawBox(viewProjectionMatrix, 0, 4 - (int)(i/5), i % 5 + count + 1.0f, GLOBAL::PLAYER_COLOR);
                    }
                    _renderer->drawVictoryTile(viewProjectionMatrix, 5 - (int)(i/5), i % 5 + count + 1.0f);
                } else {
                    _renderer->drawFloorTile(viewProjectionMatrix, 5 - (int)(i/5), i % 5 + count + 1.0f);
                }
            }
            for (int i = 0; i < 7; i++) {
                _renderer->drawFloorTile(viewProjectionMatrix, i, count);
            }
            count += 1;
            for (int i = 0; i < 5; i++) {
                _renderer->drawFloorTile(viewProjectionMatrix, 0, count+i);
                _renderer->drawFloorTile(viewProjectionMatrix, 6, count+i);
            }
            count += 5;
        }
        for (int i = 0; i < 7; i++) {
            _renderer->drawFloorTile(viewProjectionMatrix, i, count);
        }
        count += 2;
    }
}

void Menu::setCamera() {
    float minZ = -1.0f;
    float maxZ = -1.0f;

    for (int i = 0; i <= _currentPeice; i++) {
        minZ = maxZ + 1.0f;
        maxZ += _options[i].size()*6.0f + 1.0f;
    }

    _cameraPos = glm::vec3(
        0,
        2.5f,
        (minZ+maxZ)/2.0f
    );

    _cameraDistance.x = maxZ - minZ;
    _cameraDistance.y = 2.5f + 3.0f;
}

glm::vec3 Menu::getCameraPos() {
    return _cameraPos;
}

glm::vec2 Menu::getCameraDistance() {
    return _cameraDistance;
}