#include <menu.h>

// LETTERS: (each bit is a block, these are the positions of the bits)
// 0  1  2  3  4
// 5  6  7  8  9
// 10 11 12 13 14
// 15 16 17 18 19
// 20 21 22 23 24

Menu::Menu(Shaders* shader) {
    _shader = shader;

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

    GLuint vertexBufferObject;

    glGenVertexArrays(1, &_blockVAO);
    glBindVertexArray(_blockVAO);

    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*36*6, vertices, GL_STATIC_DRAW);

    GLuint attrib;
    attrib = _shader->getAttributeLocation("position");
    glEnableVertexAttribArray(attrib);
    glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), 0);

    attrib = _shader->getAttributeLocation("normal");
    glEnableVertexAttribArray(attrib);
    glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));


    glGenVertexArrays(1, &_lineVAO);
    glBindVertexArray(_lineVAO);

    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*8*3*3, lineVertecies, GL_STATIC_DRAW);

    attrib = _shader->getAttributeLocation("position");
    glEnableVertexAttribArray(attrib);
    glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), 0);
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

void Menu::update() {
    if (_wait) {
        _frame += 1;
        if (_frame >= GLOBAL::FRAMES) {
            _wait = false;
            _frame = 0;
        }
    } else if (_isTransition) {
        _frame += 1;

        float mu = (float)_frame/GLOBAL::FRAMES;
        mu = (mu * mu);
        _angle = 90.0f*(1-mu);
        _height = mu*(-GLOBAL::GAP*4);
        
        mu = (float)_frame/GLOBAL::FRAMES;
        mu = (mu * mu * (3 - 2 * (mu)));
        _cameraPos = _oldCameraPos*(1.0f-mu) + _newCameraPos*mu;
        _cameraDistance = _oldCameraDistance*(1.0f-mu) + _newCameraDistance*mu;

        if (_frame >= GLOBAL::FRAMES) {
            _isTransition = false;
            _wait = true;
            _isEndTransition = true;
            _oldCameraDistance = _newCameraDistance;
            _oldCameraPos = _newCameraPos;
            _newCameraPos.y += -GLOBAL::FALL_HEIGHT*_cameraDistance.y;
            _frame = 0;
        }
    } else if (_isCameraTransition) {
        _frame += 1;
        float mu = (float)_frame/GLOBAL::FRAMES;
        mu = (mu * mu * (3 - 2 * (mu)));
        _cameraPos = _oldCameraPos*(1.0f-mu) + _newCameraPos*mu;
        _cameraDistance = _oldCameraDistance*(1.0f-mu) + _newCameraDistance*mu;
        if (_frame >= GLOBAL::FRAMES) {
            _isCameraTransition = false;
            _oldCameraDistance = _newCameraDistance;
            _oldCameraPos = _newCameraPos;
            _frame = 0;
        }
    } else if (_isEndTransition) {
        _frame += 1;
        float mu = (float)_frame/GLOBAL::FRAMES;
        mu = (mu * mu);
        _cameraPos = _oldCameraPos*(1.0f-mu) + _newCameraPos*mu;
        _cameraDistance = _oldCameraDistance*(1.0f-mu) + _newCameraDistance*mu;
        if (_frame >= GLOBAL::FRAMES) {
            _isCameraTransition = false;
            _done = true;
            _oldCameraDistance = _newCameraDistance;
            _oldCameraPos = _newCameraPos;
            _frame = 0;
        }
    } else if (_isBeginning) {
        _frame += 1;
        float mu = (float)_frame/GLOBAL::FRAMES;
        mu = (mu * mu);
        _cameraPos = _oldCameraPos*(1.0f-mu) + _newCameraPos*mu;
        _cameraDistance = _oldCameraDistance*(1.0f-mu) + _newCameraDistance*mu;
        if (_frame >= GLOBAL::FRAMES) {
            _isBeginning = false;
            _oldCameraDistance = _newCameraDistance;
            _oldCameraPos = _newCameraPos;
            _frame = 0;
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
    _frame = 0;
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

    update();
}

unsigned int Menu::loadLetter(bool bits[25]) {
    unsigned int letter = 0;
    for (int i = 0; i < 25; i++) {
        letter += bits[i] << i;
    }
    return letter;
}

void Menu::draw(glm::mat4 viewProjectionMatrix) {
    _shader->use();
    int count = -1;
    glm::mat4 model;
    for (int m = 0; m < _options.size(); m++) {
        for (int n = 0; n < _options[m].size(); n++) {
            int letter = _options[m][n];
            for (int i = 0; i < 25; i++) {
                if (letter & (unsigned int)(1 << i)) {
                    if (m == _currentPeice) {
                        if (!_isEndTransition || _forcedEnd) {
                            model = (
                                glm::translate(glm::mat4(1.0f), -glm::vec3(-0.5f, 0, 0))
                                * glm::rotate(glm::mat4(1.0f), glm::radians(_angle), glm::vec3(0, 0, 1))
                                * glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, 0, 0))
                                * glm::scale(glm::mat4(1.0f), glm::vec3(GLOBAL::BLOCK_WIDTH, GLOBAL::BLOCK_WIDTH, GLOBAL::BLOCK_WIDTH))
                                * glm::translate(
                                    glm::mat4(1.0f), 
                                    glm::vec3(
                                        (5 - (int)(i/5)) * (1.0/(GLOBAL::BLOCK_WIDTH)),
                                        (_height+0.5f) * (1.0/(GLOBAL::BLOCK_WIDTH)),
                                        (i % 5 + count + 1.0f) * (1.0/(GLOBAL::BLOCK_WIDTH))
                                    )
                                )
                            );
                            glUniformMatrix4fv(
                                _shader->getUniformLocation("transformMatrix"), 
                                1, 
                                GL_FALSE, 
                                glm::value_ptr(viewProjectionMatrix*model)
                            );
                            glUniformMatrix4fv(
                                _shader->getUniformLocation("model"), 
                                1, 
                                GL_FALSE, 
                                glm::value_ptr(model)
                            );
                            glUniform1i(_shader->getUniformLocation("useLighting"), true);
                            glUniform3f(_shader->getUniformLocation("color"), GLOBAL::PLAYER_COLOR.x, GLOBAL::PLAYER_COLOR.y, GLOBAL::PLAYER_COLOR.z);
                            glBindVertexArray(_blockVAO);
                            glDrawArrays(GL_TRIANGLES, 0, 36);
                            // glUniform1i(_shader->getUniformLocation("useLighting"), false);
                            // glUniform3f(_shader->getUniformLocation("color"), GLOBAL::PLAYER_BORDER.x, GLOBAL::PLAYER_BORDER.y, GLOBAL::PLAYER_BORDER.z);
                            // glBindVertexArray(_lineVAO);
                            // glDrawArrays(GL_LINES, 0, 24);
                        } else {
                            model = (
                                glm::scale(glm::mat4(1.0f), glm::vec3(GLOBAL::BLOCK_WIDTH, GLOBAL::BLOCK_WIDTH, GLOBAL::BLOCK_WIDTH))
                                * glm::translate(
                                    glm::mat4(1.0f), 
                                    glm::vec3(
                                        (5 - (int)(i/5)) * (1.0/(GLOBAL::BLOCK_WIDTH)),
                                        (_height+0.5f) * (1.0/(GLOBAL::BLOCK_WIDTH)),
                                        (i % 5 + count + 1.0f) * (1.0/(GLOBAL::BLOCK_WIDTH))
                                    )
                                )
                            );
                            glUniformMatrix4fv(
                                _shader->getUniformLocation("transformMatrix"), 
                                1, 
                                GL_FALSE, 
                                glm::value_ptr(viewProjectionMatrix*model)
                            );
                            glUniformMatrix4fv(
                                _shader->getUniformLocation("model"), 
                                1, 
                                GL_FALSE, 
                                glm::value_ptr(model)
                            );
                            glUniform1i(_shader->getUniformLocation("useLighting"), true);
                            glUniform3f(_shader->getUniformLocation("color"), GLOBAL::VICTORY_COLOR.x, GLOBAL::VICTORY_COLOR.y, GLOBAL::VICTORY_COLOR.z);
                            glBindVertexArray(_blockVAO);
                            glDrawArrays(GL_TRIANGLES, 0, 36);
                            // glUniform1i(_shader->getUniformLocation("useLighting"), false);
                            // glUniform3f(_shader->getUniformLocation("color"), GLOBAL::PLAYER_BORDER.x, GLOBAL::PLAYER_BORDER.y, GLOBAL::PLAYER_BORDER.z);
                            // glBindVertexArray(_lineVAO);
                            // glDrawArrays(GL_LINES, 0, 24);
                        }
                    } else {
                        model = (
                            glm::scale(glm::mat4(1.0f), glm::vec3(GLOBAL::BLOCK_WIDTH, GLOBAL::BLOCK_WIDTH, GLOBAL::BLOCK_WIDTH))
                            * glm::translate(
                                glm::mat4(1.0f), 
                                glm::vec3(
                                    0,
                                    (4 - (int)(i/5) + 0.5f) * (1.0/(GLOBAL::BLOCK_WIDTH)),
                                    (i % 5 + count + 1.0f) * (1.0/(GLOBAL::BLOCK_WIDTH))
                                )
                            )
                        );
                        glUniformMatrix4fv(
                            _shader->getUniformLocation("transformMatrix"), 
                            1, 
                            GL_FALSE, 
                            glm::value_ptr(viewProjectionMatrix*model)
                        );
                        glUniformMatrix4fv(
                            _shader->getUniformLocation("model"), 
                            1, 
                            GL_FALSE, 
                            glm::value_ptr(model)
                        );
                        glUniform1i(_shader->getUniformLocation("useLighting"), true);
                        glUniform3f(_shader->getUniformLocation("color"), GLOBAL::PLAYER_COLOR.x, GLOBAL::PLAYER_COLOR.y, GLOBAL::PLAYER_COLOR.z);
                        glBindVertexArray(_blockVAO);
                        glDrawArrays(GL_TRIANGLES, 0, 36);
                        // glUniform1i(_shader->getUniformLocation("useLighting"), false);
                        // glUniform3f(_shader->getUniformLocation("color"), GLOBAL::STATIC_BORDER.x, GLOBAL::STATIC_BORDER.y, GLOBAL::STATIC_BORDER.z);
                        // glBindVertexArray(_lineVAO);
                        // glDrawArrays(GL_LINES, 0, 24);
                    }

                    model = (
                        glm::translate(
                            glm::mat4(1.0f),
                            glm::vec3(
                                (5 - (int)(i/5)),
                                -GLOBAL::GAP*5,
                                (i % 5 + count + 1.0f)
                            )
                        )
                        * glm::scale(glm::mat4(1.0f), glm::vec3(GLOBAL::BLOCK_WIDTH, 2-(GLOBAL::GAP*6), GLOBAL::BLOCK_WIDTH))
                        * glm::translate(
                            glm::mat4(1.0f),
                            glm::vec3(0, -0.5, 0)
                        )
                    );
                    glUniformMatrix4fv(
                        _shader->getUniformLocation("transformMatrix"), 
                        1, 
                        GL_FALSE, 
                        glm::value_ptr(viewProjectionMatrix*model)
                    );
                    glUniformMatrix4fv(
                        _shader->getUniformLocation("model"), 
                        1, 
                        GL_FALSE, 
                        glm::value_ptr(model)
                    );
                    glUniform1i(_shader->getUniformLocation("useLighting"), true);
                    glUniform3f(_shader->getUniformLocation("color"), GLOBAL::VICTORY_COLOR.x, GLOBAL::VICTORY_COLOR.y, GLOBAL::VICTORY_COLOR.z);
                    glBindVertexArray(_blockVAO);
                    glDrawArrays(GL_TRIANGLES, 0, 36);
                    // glUniform1i(_shader->getUniformLocation("useLighting"), false);
                    // glUniform3f(_shader->getUniformLocation("color"), GLOBAL::FLOOR_BORDER.x, GLOBAL::FLOOR_BORDER.y, GLOBAL::FLOOR_BORDER.z);
                    // glBindVertexArray(_lineVAO);
                    // glDrawArrays(GL_LINES, 0, 24);
                } else {
                    model = (
                        glm::translate(
                            glm::mat4(1.0f),
                            glm::vec3(
                                (5 - (int)(i/5)),
                                -1,
                                (i % 5 + count + 1.0f)
                            )
                        )
                        * glm::scale(glm::mat4(1.0f), glm::vec3(GLOBAL::BLOCK_WIDTH, 2-(GLOBAL::GAP*2), GLOBAL::BLOCK_WIDTH))
                    );
                    glUniformMatrix4fv(
                        _shader->getUniformLocation("transformMatrix"), 
                        1, 
                        GL_FALSE, 
                        glm::value_ptr(viewProjectionMatrix*model)
                    );
                    glUniformMatrix4fv(
                        _shader->getUniformLocation("model"), 
                        1, 
                        GL_FALSE, 
                        glm::value_ptr(model)
                    );
                    glUniform1i(_shader->getUniformLocation("useLighting"), true);
                    glUniform3f(_shader->getUniformLocation("color"), GLOBAL::FLOOR_COLOR.x, GLOBAL::FLOOR_COLOR.y, GLOBAL::FLOOR_COLOR.z);
                    glBindVertexArray(_blockVAO);
                    glDrawArrays(GL_TRIANGLES, 0, 36);
                    // glUniform1i(_shader->getUniformLocation("useLighting"), false);
                    // glUniform3f(_shader->getUniformLocation("color"), GLOBAL::FLOOR_BORDER.x, GLOBAL::FLOOR_BORDER.y, GLOBAL::FLOOR_BORDER.z);
                    // glBindVertexArray(_lineVAO);
                    // glDrawArrays(GL_LINES, 0, 24);
                }
            }
            for (int i = 0; i < 7; i++) {
                model = (
                    glm::translate(
                        glm::mat4(1.0f),
                        glm::vec3(
                            i,
                            -1,
                            count
                        )
                    )
                    * glm::scale(glm::mat4(1.0f), glm::vec3(GLOBAL::BLOCK_WIDTH, 2-(GLOBAL::GAP*2), GLOBAL::BLOCK_WIDTH))
                );
                glUniformMatrix4fv(
                    _shader->getUniformLocation("transformMatrix"), 
                    1, 
                    GL_FALSE, 
                    glm::value_ptr(viewProjectionMatrix*model)
                );
                glUniformMatrix4fv(
                    _shader->getUniformLocation("model"), 
                    1, 
                    GL_FALSE, 
                    glm::value_ptr(model)
                );
                glUniform1i(_shader->getUniformLocation("useLighting"), true);
                glUniform3f(_shader->getUniformLocation("color"), GLOBAL::FLOOR_COLOR.x, GLOBAL::FLOOR_COLOR.y, GLOBAL::FLOOR_COLOR.z);
                glBindVertexArray(_blockVAO);
                glDrawArrays(GL_TRIANGLES, 0, 36);
                // glUniform1i(_shader->getUniformLocation("useLighting"), false);
                // glUniform3f(_shader->getUniformLocation("color"), GLOBAL::FLOOR_BORDER.x, GLOBAL::FLOOR_BORDER.y, GLOBAL::FLOOR_BORDER.z);
                // glBindVertexArray(_lineVAO);
                // glDrawArrays(GL_LINES, 0, 24);
            }
            count += 1;
            for (int i = 0; i < 5; i++) {
                model = (
                    glm::translate(
                        glm::mat4(1.0f),
                        glm::vec3(
                            0,
                            -1,
                            count+i
                        )
                    )
                    * glm::scale(glm::mat4(1.0f), glm::vec3(GLOBAL::BLOCK_WIDTH, 2-(GLOBAL::GAP*2), GLOBAL::BLOCK_WIDTH))
                );
                glUniformMatrix4fv(
                    _shader->getUniformLocation("transformMatrix"), 
                    1, 
                    GL_FALSE, 
                    glm::value_ptr(viewProjectionMatrix*model)
                );
                glUniformMatrix4fv(
                    _shader->getUniformLocation("model"), 
                    1, 
                    GL_FALSE, 
                    glm::value_ptr(model)
                );
                glUniform1i(_shader->getUniformLocation("useLighting"), true);
                glUniform3f(_shader->getUniformLocation("color"), GLOBAL::FLOOR_COLOR.x, GLOBAL::FLOOR_COLOR.y, GLOBAL::FLOOR_COLOR.z);
                glBindVertexArray(_blockVAO);
                glDrawArrays(GL_TRIANGLES, 0, 36);
                // glUniform1i(_shader->getUniformLocation("useLighting"), false);
                // glUniform3f(_shader->getUniformLocation("color"), GLOBAL::FLOOR_BORDER.x, GLOBAL::FLOOR_BORDER.y, GLOBAL::FLOOR_BORDER.z);
                // glBindVertexArray(_lineVAO);
                // glDrawArrays(GL_LINES, 0, 24);

                model = (
                    glm::translate(
                        glm::mat4(1.0f),
                        glm::vec3(
                            6,
                            -1,
                            count+i
                        )
                    )
                    * glm::scale(glm::mat4(1.0f), glm::vec3(GLOBAL::BLOCK_WIDTH, 2-(GLOBAL::GAP*2), GLOBAL::BLOCK_WIDTH))
                );
                glUniformMatrix4fv(
                    _shader->getUniformLocation("transformMatrix"), 
                    1, 
                    GL_FALSE, 
                    glm::value_ptr(viewProjectionMatrix*model)
                );
                glUniformMatrix4fv(
                    _shader->getUniformLocation("model"), 
                    1, 
                    GL_FALSE, 
                    glm::value_ptr(model)
                );
                glUniform1i(_shader->getUniformLocation("useLighting"), true);
                glUniform3f(_shader->getUniformLocation("color"), GLOBAL::FLOOR_COLOR.x, GLOBAL::FLOOR_COLOR.y, GLOBAL::FLOOR_COLOR.z);
                glBindVertexArray(_blockVAO);
                glDrawArrays(GL_TRIANGLES, 0, 36);
                // glUniform1i(_shader->getUniformLocation("useLighting"), false);
                // glUniform3f(_shader->getUniformLocation("color"), GLOBAL::FLOOR_BORDER.x, GLOBAL::FLOOR_BORDER.y, GLOBAL::FLOOR_BORDER.z);
                // glBindVertexArray(_lineVAO);
                // glDrawArrays(GL_LINES, 0, 24);
            }
            count += 5;
        }
        for (int i = 0; i < 7; i++) {
            model = (
                glm::translate(
                    glm::mat4(1.0f),
                    glm::vec3(
                        i,
                        -1,
                        count
                    )
                )
                * glm::scale(glm::mat4(1.0f), glm::vec3(GLOBAL::BLOCK_WIDTH, 2-(GLOBAL::GAP*2), GLOBAL::BLOCK_WIDTH))
            );
            glUniformMatrix4fv(
                _shader->getUniformLocation("transformMatrix"), 
                1, 
                GL_FALSE, 
                glm::value_ptr(viewProjectionMatrix*model)
            );
            glUniformMatrix4fv(
                _shader->getUniformLocation("model"), 
                1, 
                GL_FALSE, 
                glm::value_ptr(model)
            );
            glUniform1i(_shader->getUniformLocation("useLighting"), true);
            glUniform3f(_shader->getUniformLocation("color"), GLOBAL::FLOOR_COLOR.x, GLOBAL::FLOOR_COLOR.y, GLOBAL::FLOOR_COLOR.z);
            glBindVertexArray(_blockVAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            // glUniform1i(_shader->getUniformLocation("useLighting"), false);
            // glUniform3f(_shader->getUniformLocation("color"), GLOBAL::FLOOR_BORDER.x, GLOBAL::FLOOR_BORDER.y, GLOBAL::FLOOR_BORDER.z);
            // glBindVertexArray(_lineVAO);
            // glDrawArrays(GL_LINES, 0, 24);
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