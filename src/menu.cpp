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
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1, 
        1, 0, 0, 0, 1,
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

    float vertices[48] = {
        -0.5,  0.5f,  -0.5, GLOBAL::PLAYER_COLOR.r, GLOBAL::PLAYER_COLOR.g, GLOBAL::PLAYER_COLOR.b,
        -0.5,  0.5f,   0.5, GLOBAL::PLAYER_COLOR.r, GLOBAL::PLAYER_COLOR.g, GLOBAL::PLAYER_COLOR.b,
         0.5,  0.5f,   0.5, GLOBAL::PLAYER_COLOR.r, GLOBAL::PLAYER_COLOR.g, GLOBAL::PLAYER_COLOR.b,
         0.5,  0.5f,  -0.5, GLOBAL::PLAYER_COLOR.r, GLOBAL::PLAYER_COLOR.g, GLOBAL::PLAYER_COLOR.b,

        -0.5, -0.5f,  -0.5, GLOBAL::PLAYER_COLOR.r, GLOBAL::PLAYER_COLOR.g, GLOBAL::PLAYER_COLOR.b,
        -0.5, -0.5f,   0.5, GLOBAL::PLAYER_COLOR.r, GLOBAL::PLAYER_COLOR.g, GLOBAL::PLAYER_COLOR.b,
         0.5, -0.5f,   0.5, GLOBAL::PLAYER_COLOR.r, GLOBAL::PLAYER_COLOR.g, GLOBAL::PLAYER_COLOR.b,
         0.5, -0.5f,  -0.5, GLOBAL::PLAYER_COLOR.r, GLOBAL::PLAYER_COLOR.g, GLOBAL::PLAYER_COLOR.b,
    };

    float floorVertecies[48] = {
        -0.5f, -GLOBAL::GAP, -0.5f, GLOBAL::FLOOR_COLOR.r, GLOBAL::FLOOR_COLOR.g, GLOBAL::FLOOR_COLOR.b,
        -0.5f, -GLOBAL::GAP,  0.5f, GLOBAL::FLOOR_COLOR.r, GLOBAL::FLOOR_COLOR.g, GLOBAL::FLOOR_COLOR.b,
         0.5f, -GLOBAL::GAP,  0.5f, GLOBAL::FLOOR_COLOR.r, GLOBAL::FLOOR_COLOR.g, GLOBAL::FLOOR_COLOR.b,
         0.5f, -GLOBAL::GAP, -0.5f, GLOBAL::FLOOR_COLOR.r, GLOBAL::FLOOR_COLOR.g, GLOBAL::FLOOR_COLOR.b,

        -0.5f,  GLOBAL::BOTTOM+GLOBAL::GAP, -0.5f, GLOBAL::FLOOR_BOTTOM.r, GLOBAL::FLOOR_BOTTOM.g, GLOBAL::FLOOR_BOTTOM.b,
        -0.5f,  GLOBAL::BOTTOM+GLOBAL::GAP,  0.5f, GLOBAL::FLOOR_BOTTOM.r, GLOBAL::FLOOR_BOTTOM.g, GLOBAL::FLOOR_BOTTOM.b,
         0.5f,  GLOBAL::BOTTOM+GLOBAL::GAP,  0.5f, GLOBAL::FLOOR_BOTTOM.r, GLOBAL::FLOOR_BOTTOM.g, GLOBAL::FLOOR_BOTTOM.b,
         0.5f,  GLOBAL::BOTTOM+GLOBAL::GAP, -0.5f, GLOBAL::FLOOR_BOTTOM.r, GLOBAL::FLOOR_BOTTOM.g, GLOBAL::FLOOR_BOTTOM.b,
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

    glGenVertexArrays(1, &_selectedVAO);
    glBindVertexArray(_selectedVAO);

    glGenBuffers(1, &elementBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*36, elements, GL_STATIC_DRAW);

    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*8*6, vertices, GL_STATIC_DRAW);

    GLuint attrib;
    attrib = _shader->getAttributeLocation("position");
    glEnableVertexAttribArray(attrib);
    glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), 0);

    attrib = _shader->getAttributeLocation("color");
    glEnableVertexAttribArray(attrib);
    glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));


    glGenVertexArrays(1, &_unselectedVAO);
    glBindVertexArray(_unselectedVAO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);

    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*8*6, vertices, GL_STATIC_DRAW);

    attrib = _shader->getAttributeLocation("position");
    glEnableVertexAttribArray(attrib);
    glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), 0);

    attrib = _shader->getAttributeLocation("color");
    glEnableVertexAttribArray(attrib);
    glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));


    glGenVertexArrays(1, &_floorVAO);
    glBindVertexArray(_floorVAO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);

    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*8*6, floorVertecies, GL_STATIC_DRAW);

    attrib = _shader->getAttributeLocation("position");
    glEnableVertexAttribArray(attrib);
    glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), 0);

    attrib = _shader->getAttributeLocation("color");
    glEnableVertexAttribArray(attrib);
    glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));


    glGenVertexArrays(1, &_selectedLineVAO);
    glBindVertexArray(_selectedLineVAO);

    glGenBuffers(1, &elementBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*24, lineElements, GL_STATIC_DRAW);

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


    glGenVertexArrays(1, &_unselectedLineVAO);
    glBindVertexArray(_unselectedLineVAO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);

    for (int i = 0; i < 8; i++) {
        vertices[i*6+3] = 1;
        vertices[i*6+4] = 1;
        vertices[i*6+5] = 1;
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


    glGenVertexArrays(1, &_floorLineVAO);
    glBindVertexArray(_floorLineVAO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);

    for (int i = 0; i < 4; i++) {
        floorVertecies[i*6+3] = 1;
        floorVertecies[i*6+4] = 1;
        floorVertecies[i*6+5] = 1;
    }

    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*8*6, floorVertecies, GL_STATIC_DRAW);

    attrib = _shader->getAttributeLocation("position");
    glEnableVertexAttribArray(attrib);
    glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), 0);

    attrib = _shader->getAttributeLocation("color");
    glEnableVertexAttribArray(attrib);
    glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));
}

void Menu::setOptions(std::string* options, int numOptions) {
    for (int n = 0; n < numOptions; n++) {
        std::vector<unsigned int> v;
        _options.push_back(v);
        for (int c = 0; c < options[n].length(); c++) {
            _options[n].push_back(_chars[options[n][c]]);
        }
    }
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
    int count = 0;
    glm::mat4 transformMatrix;
    for (auto word: _options) {
        for (int n = 0; n < word.size(); n++) {
            int letter = word[n];
            for (int i = 0; i < 25; i++) {
                if (letter & (unsigned int)(1 << i)) {
                    transformMatrix = (
                        viewProjectionMatrix
                        // * glm::translate(glm::mat4(1.0f), -_rotationAxisPosition)
                        // * glm::rotate(glm::mat4(1.0f), glm::radians(_angleSign*_angle), _rotationAxis)
                        // * glm::translate(glm::mat4(1.0f), _rotationAxisPosition)
                        * glm::scale(glm::mat4(1.0f), glm::vec3(GLOBAL::BLOCK_WIDTH, GLOBAL::BLOCK_WIDTH, GLOBAL::BLOCK_WIDTH))
                        * glm::translate(
                            glm::mat4(1.0f), 
                            glm::vec3(
                                0,
                                (4 - (int)(i/5) + 0.5f) * (1.0/(GLOBAL::BLOCK_WIDTH)),
                                (i % 5 + count) * (1.0/(GLOBAL::BLOCK_WIDTH))
                            )
                        )
                    );
                    glUniformMatrix4fv(
                        _shader->getUniformLocation("transformMatrix"), 
                        1, 
                        GL_FALSE, 
                        glm::value_ptr(transformMatrix)
                    );
                    glBindVertexArray(_selectedVAO);
                    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
                    glBindVertexArray(_selectedLineVAO);
                    glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);
                }
            }
            for (int i = 0; i < 5; i++) {
                transformMatrix = viewProjectionMatrix
                * glm::scale(glm::mat4(1.0f), glm::vec3(GLOBAL::BLOCK_WIDTH, 1, GLOBAL::BLOCK_WIDTH))
                * glm::translate(
                    glm::mat4(1.0f),
                    glm::vec3(
                        0,
                        0,
                        (count+i) * (1.0/(GLOBAL::BLOCK_WIDTH))
                    )
                );
                glUniformMatrix4fv(
                    _shader->getUniformLocation("transformMatrix"), 
                    1, 
                    GL_FALSE, 
                    glm::value_ptr(transformMatrix)
                );
                glBindVertexArray(_floorVAO);
                glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
                glBindVertexArray(_floorLineVAO);
                glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);
            }
            count += 5;
            if (n < word.size()-1) {
                transformMatrix = viewProjectionMatrix
                * glm::scale(glm::mat4(1.0f), glm::vec3(GLOBAL::BLOCK_WIDTH, 1, GLOBAL::BLOCK_WIDTH))
                * glm::translate(
                    glm::mat4(1.0f),
                    glm::vec3(
                        0,
                        0,
                        (count) * (1.0/(GLOBAL::BLOCK_WIDTH))
                    )
                );
                glUniformMatrix4fv(
                    _shader->getUniformLocation("transformMatrix"), 
                    1, 
                    GL_FALSE, 
                    glm::value_ptr(transformMatrix)
                );
                glBindVertexArray(_floorVAO);
                glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
                glBindVertexArray(_floorLineVAO);
                glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);
                count += 1;
            }
        }
        count += 2;
    }
}