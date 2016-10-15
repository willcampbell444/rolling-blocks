#include <floor.h>

const float GAP = GLOBAL::GAP;
const float BOTTOM = GLOBAL::BOTTOM;

Floor::Floor(Shaders* shader) {
    glGenVertexArrays(1, &_vertexArrayObject);
    glBindVertexArray(_vertexArrayObject);

    glGenBuffers(1, &_elementBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBufferObject);

    glGenBuffers(1, &_vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObject);

    glGenVertexArrays(1, &_lineVertexArrayObject);
    glBindVertexArray(_lineVertexArrayObject);

    glGenBuffers(1, &_lineElementBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _lineElementBufferObject);

    glGenBuffers(1, &_lineVertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, _lineVertexBufferObject);

    _shader = shader;
}

Floor::~Floor() {
    glDeleteBuffers(1, &_vertexBufferObject);
    glDeleteBuffers(1, &_elementBufferObject);
    glDeleteVertexArrays(1, &_vertexArrayObject);
}

void Floor::create(int width, int length, unsigned char* tiles) {
    _width = width;
    _length = length;

    _map = tiles;

    _numFilled = _width*_length;
    for (int i = 0; i < _width*_length; i++) {
        if (_map[i] == 0) {
            _numFilled -= 1;
        }
    }

    float* vertices = new float[_numFilled*8*6];
    float* lineVertices = new float[_numFilled*8*6];

    int count = 0;
    int tileCount = 0;

    for (float i = -(width)/2.0f; i < (width)/2.0f; i += 1.0f) {
        for (float j = -(length)/2.0f; j < (length)/2.0f; j += 1.0f) {
            if (_map[tileCount] == 1) {
                vertices[ count ]  = i+GAP;
                vertices[count+1]  = -GAP;
                vertices[count+2]  = j+GAP;

                vertices[count+3]  = GLOBAL::FLOOR_COLOR.r;
                vertices[count+4]  = GLOBAL::FLOOR_COLOR.g;
                vertices[count+5]  = GLOBAL::FLOOR_COLOR.b;

                vertices[count+6]  = i+1-GAP;
                vertices[count+7]  = -GAP;
                vertices[count+8]  = j+GAP;

                vertices[count+9]  = GLOBAL::FLOOR_COLOR.r;
                vertices[count+10]  = GLOBAL::FLOOR_COLOR.g;
                vertices[count+11]  = GLOBAL::FLOOR_COLOR.b;

                vertices[count+12]  = i+1-GAP;
                vertices[count+13]  = -GAP;
                vertices[count+14]  = j+1-GAP;

                vertices[count+15]  = GLOBAL::FLOOR_COLOR.r;
                vertices[count+16]  = GLOBAL::FLOOR_COLOR.g;
                vertices[count+17]  = GLOBAL::FLOOR_COLOR.b;

                vertices[count+18]  = i+GAP;
                vertices[count+19] = -GAP;
                vertices[count+20] = j+1-GAP;

                vertices[count+21]  = GLOBAL::FLOOR_COLOR.r;
                vertices[count+22]  = GLOBAL::FLOOR_COLOR.g;
                vertices[count+23]  = GLOBAL::FLOOR_COLOR.b;

                vertices[count+24] = i+GAP;
                vertices[count+25] = BOTTOM+GAP;
                vertices[count+26] = j+GAP;


                vertices[count+27]  = GLOBAL::FLOOR_BOTTOM.r;
                vertices[count+28]  = GLOBAL::FLOOR_BOTTOM.g;
                vertices[count+29]  = GLOBAL::FLOOR_BOTTOM.b;

                vertices[count+30] = i+1-GAP;
                vertices[count+31] = BOTTOM+GAP;
                vertices[count+32] = j+GAP;

                vertices[count+33]  = GLOBAL::FLOOR_BOTTOM.r;
                vertices[count+34]  = GLOBAL::FLOOR_BOTTOM.g;
                vertices[count+35]  = GLOBAL::FLOOR_BOTTOM.b;

                vertices[count+36] = i+1-GAP;
                vertices[count+37] = BOTTOM+GAP;
                vertices[count+38] = j+1-GAP;

                vertices[count+39]  = GLOBAL::FLOOR_BOTTOM.r;
                vertices[count+40]  = GLOBAL::FLOOR_BOTTOM.g;
                vertices[count+41]  = GLOBAL::FLOOR_BOTTOM.b;

                vertices[count+42] = i+GAP;
                vertices[count+43] = BOTTOM+GAP;
                vertices[count+44] = j+1-GAP;

                vertices[count+45]  = GLOBAL::FLOOR_BOTTOM.r;
                vertices[count+46]  = GLOBAL::FLOOR_BOTTOM.g;
                vertices[count+47]  = GLOBAL::FLOOR_BOTTOM.b;

                count += 48;
            } else if (_map[tileCount] == 2) {
                vertices[ count ]  = i+GAP;
                vertices[count+1]  = -5*GAP;
                vertices[count+2]  = j+GAP;

                vertices[count+3]  = GLOBAL::VICTORY_COLOR.r;
                vertices[count+4]  = GLOBAL::VICTORY_COLOR.g;
                vertices[count+5]  = GLOBAL::VICTORY_COLOR.b;

                vertices[count+6]  = i+1-GAP;
                vertices[count+7]  = -5*GAP;
                vertices[count+8]  = j+GAP;

                vertices[count+9]  = GLOBAL::VICTORY_COLOR.r;
                vertices[count+10]  = GLOBAL::VICTORY_COLOR.g;
                vertices[count+11]  = GLOBAL::VICTORY_COLOR.b;

                vertices[count+12]  = i+1-GAP;
                vertices[count+13]  = -5*GAP;
                vertices[count+14]  = j+1-GAP;

                vertices[count+15]  = GLOBAL::VICTORY_COLOR.r;
                vertices[count+16]  = GLOBAL::VICTORY_COLOR.g;
                vertices[count+17]  = GLOBAL::VICTORY_COLOR.b;

                vertices[count+18]  = i+GAP;
                vertices[count+19] = -5*GAP;
                vertices[count+20] = j+1-GAP;

                vertices[count+21]  = GLOBAL::VICTORY_COLOR.r;
                vertices[count+22]  = GLOBAL::VICTORY_COLOR.g;
                vertices[count+23]  = GLOBAL::VICTORY_COLOR.b;

                vertices[count+24] = i+GAP;
                vertices[count+25] = BOTTOM+GAP;
                vertices[count+26] = j+GAP;


                vertices[count+27]  = GLOBAL::FLOOR_BOTTOM.r;
                vertices[count+28]  = GLOBAL::FLOOR_BOTTOM.g;
                vertices[count+29]  = GLOBAL::FLOOR_BOTTOM.b;

                vertices[count+30] = i+1-GAP;
                vertices[count+31] = BOTTOM+GAP;
                vertices[count+32] = j+GAP;

                vertices[count+33]  = GLOBAL::FLOOR_BOTTOM.r;
                vertices[count+34]  = GLOBAL::FLOOR_BOTTOM.g;
                vertices[count+35]  = GLOBAL::FLOOR_BOTTOM.b;

                vertices[count+36] = i+1-GAP;
                vertices[count+37] = BOTTOM+GAP;
                vertices[count+38] = j+1-GAP;

                vertices[count+39]  = GLOBAL::FLOOR_BOTTOM.r;
                vertices[count+40]  = GLOBAL::FLOOR_BOTTOM.g;
                vertices[count+41]  = GLOBAL::FLOOR_BOTTOM.b;

                vertices[count+42] = i+GAP;
                vertices[count+43] = BOTTOM+GAP;
                vertices[count+44] = j+1-GAP;

                vertices[count+45]  = GLOBAL::FLOOR_BOTTOM.r;
                vertices[count+46]  = GLOBAL::FLOOR_BOTTOM.g;
                vertices[count+47]  = GLOBAL::FLOOR_BOTTOM.b;

                count += 48;
            }
            tileCount += 1;
        }
    }

    count = 0;
    tileCount = 0;

    for (float i = -(width)/2.0f; i < (width)/2.0f; i += 1.0f) {
        for (float j = -(length)/2.0f; j < (length)/2.0f; j += 1.0f) {
            if (_map[tileCount] == 1) {
                lineVertices[ count ]  = i+GAP;
                lineVertices[count+1]  = -GAP;
                lineVertices[count+2]  = j+GAP;

                lineVertices[count+3]  = GLOBAL::FLOOR_BORDER.r;
                lineVertices[count+4]  = GLOBAL::FLOOR_BORDER.g;
                lineVertices[count+5]  = GLOBAL::FLOOR_BORDER.b;

                lineVertices[count+6]  = i+1-GAP;
                lineVertices[count+7]  = -GAP;
                lineVertices[count+8]  = j+GAP;

                lineVertices[count+9]  = GLOBAL::FLOOR_BORDER.r;
                lineVertices[count+10]  = GLOBAL::FLOOR_BORDER.g;
                lineVertices[count+11]  = GLOBAL::FLOOR_BORDER.b;

                lineVertices[count+12]  = i+1-GAP;
                lineVertices[count+13]  = -GAP;
                lineVertices[count+14]  = j+1-GAP;

                lineVertices[count+15]  = GLOBAL::FLOOR_BORDER.r;
                lineVertices[count+16]  = GLOBAL::FLOOR_BORDER.g;
                lineVertices[count+17]  = GLOBAL::FLOOR_BORDER.b;

                lineVertices[count+18]  = i+GAP;
                lineVertices[count+19] = -GAP;
                lineVertices[count+20] = j+1-GAP;

                lineVertices[count+21]  = GLOBAL::FLOOR_BORDER.r;
                lineVertices[count+22]  = GLOBAL::FLOOR_BORDER.g;
                lineVertices[count+23]  = GLOBAL::FLOOR_BORDER.b;

                lineVertices[count+24] = i+GAP;
                lineVertices[count+25] = BOTTOM+GAP;
                lineVertices[count+26] = j+GAP;

                lineVertices[count+27]  = GLOBAL::FLOOR_BOTTOM.r;
                lineVertices[count+28]  = GLOBAL::FLOOR_BOTTOM.g;
                lineVertices[count+29]  = GLOBAL::FLOOR_BOTTOM.b;

                lineVertices[count+30] = i+1-GAP;
                lineVertices[count+31] = BOTTOM+GAP;
                lineVertices[count+32] = j+GAP;

                lineVertices[count+33]  = GLOBAL::FLOOR_BOTTOM.r;
                lineVertices[count+34]  = GLOBAL::FLOOR_BOTTOM.g;
                lineVertices[count+35]  = GLOBAL::FLOOR_BOTTOM.b;

                lineVertices[count+36] = i+1-GAP;
                lineVertices[count+37] = BOTTOM+GAP;
                lineVertices[count+38] = j+1-GAP;

                lineVertices[count+39]  = GLOBAL::FLOOR_BOTTOM.r;
                lineVertices[count+40]  = GLOBAL::FLOOR_BOTTOM.g;
                lineVertices[count+41]  = GLOBAL::FLOOR_BOTTOM.b;

                lineVertices[count+42] = i+GAP;
                lineVertices[count+43] = BOTTOM+GAP;
                lineVertices[count+44] = j+1-GAP;

                lineVertices[count+45]  = GLOBAL::FLOOR_BOTTOM.r;
                lineVertices[count+46]  = GLOBAL::FLOOR_BOTTOM.g;
                lineVertices[count+47]  = GLOBAL::FLOOR_BOTTOM.b;

                count += 48;
            } else if (_map[tileCount] == 2) {
                lineVertices[ count ]  = i+GAP;
                lineVertices[count+1]  = -5*GAP;
                lineVertices[count+2]  = j+GAP;

                lineVertices[count+3]  = GLOBAL::VICTORY_BORDER.r;
                lineVertices[count+4]  = GLOBAL::VICTORY_BORDER.g;
                lineVertices[count+5]  = GLOBAL::VICTORY_BORDER.b;

                lineVertices[count+6]  = i+1-GAP;
                lineVertices[count+7]  = -5*GAP;
                lineVertices[count+8]  = j+GAP;

                lineVertices[count+9]  = GLOBAL::VICTORY_BORDER.r;
                lineVertices[count+10]  = GLOBAL::VICTORY_BORDER.g;
                lineVertices[count+11]  = GLOBAL::VICTORY_BORDER.b;

                lineVertices[count+12]  = i+1-GAP;
                lineVertices[count+13]  = -5*GAP;
                lineVertices[count+14]  = j+1-GAP;

                lineVertices[count+15]  = GLOBAL::VICTORY_BORDER.r;
                lineVertices[count+16]  = GLOBAL::VICTORY_BORDER.g;
                lineVertices[count+17]  = GLOBAL::VICTORY_BORDER.b;

                lineVertices[count+18]  = i+GAP;
                lineVertices[count+19] = -5*GAP;
                lineVertices[count+20] = j+1-GAP;

                lineVertices[count+21]  = GLOBAL::VICTORY_BORDER.r;
                lineVertices[count+22]  = GLOBAL::VICTORY_BORDER.g;
                lineVertices[count+23]  = GLOBAL::VICTORY_BORDER.b;

                lineVertices[count+24] = i+GAP;
                lineVertices[count+25] = BOTTOM+GAP;
                lineVertices[count+26] = j+GAP;

                lineVertices[count+27]  = GLOBAL::FLOOR_BOTTOM.r;
                lineVertices[count+28]  = GLOBAL::FLOOR_BOTTOM.g;
                lineVertices[count+29]  = GLOBAL::FLOOR_BOTTOM.b;

                lineVertices[count+30] = i+1-GAP;
                lineVertices[count+31] = BOTTOM+GAP;
                lineVertices[count+32] = j+GAP;

                lineVertices[count+33]  = GLOBAL::FLOOR_BOTTOM.r;
                lineVertices[count+34]  = GLOBAL::FLOOR_BOTTOM.g;
                lineVertices[count+35]  = GLOBAL::FLOOR_BOTTOM.b;

                lineVertices[count+36] = i+1-GAP;
                lineVertices[count+37] = BOTTOM+GAP;
                lineVertices[count+38] = j+1-GAP;

                lineVertices[count+39]  = GLOBAL::FLOOR_BOTTOM.r;
                lineVertices[count+40]  = GLOBAL::FLOOR_BOTTOM.g;
                lineVertices[count+41]  = GLOBAL::FLOOR_BOTTOM.b;

                lineVertices[count+42] = i+GAP;
                lineVertices[count+43] = BOTTOM+GAP;
                lineVertices[count+44] = j+1-GAP;

                lineVertices[count+45]  = GLOBAL::FLOOR_BOTTOM.r;
                lineVertices[count+46]  = GLOBAL::FLOOR_BOTTOM.g;
                lineVertices[count+47]  = GLOBAL::FLOOR_BOTTOM.b;

                count += 48;
            }
            tileCount += 1;
        }
    }

    GLuint cube[36] = {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4,
        4, 5, 1, 1, 0, 4,
        6, 7, 3, 3, 2, 6,
        4, 0, 3, 3, 7, 4,
        5, 1, 2, 2, 6, 5
    };

    GLuint* elements = new GLuint[_numFilled*6*6];

    for (int x = 0; x < _numFilled; x++) {
        for (int y = 0; y < 36; y++) {
            elements[(x*36)+y] = (x*8)+cube[y];
        }
    }

    GLuint lineCube[24] = {
        0, 1,
        1, 2,
        2, 3,
        3, 0,

        4, 5,
        5, 6,
        6, 7,
        7, 4,

        0, 4,
        1, 5,
        2, 6,
        3, 7
    };

    GLuint* lineElements = new GLuint[_numFilled*24];

    for (int x = 0; x < _numFilled; x++) {
        for (int y = 0; y < 24; y++) {
            lineElements[(x*24)+y] = (x*8)+lineCube[y];
        }
    }

    glBindVertexArray(_vertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBufferObject);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4*_numFilled*6*6, elements, GL_STATIC_DRAW);
    delete elements;

    glBufferData(GL_ARRAY_BUFFER, 4*_numFilled*8*6, vertices, GL_STATIC_DRAW);
    delete vertices;

    GLuint attrib = _shader->getAttributeLocation("color");
    glEnableVertexAttribArray(attrib);
    glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));

    attrib = _shader->getAttributeLocation("position");
    glEnableVertexAttribArray(attrib);
    glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), 0);


    glBindVertexArray(_lineVertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, _lineVertexBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _lineElementBufferObject);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4*_numFilled*24, lineElements, GL_STATIC_DRAW);
    delete lineElements;

    glBufferData(GL_ARRAY_BUFFER, 4*_numFilled*8*6, lineVertices, GL_STATIC_DRAW);
    delete lineVertices;
    attrib = _shader->getAttributeLocation("position");
    glEnableVertexAttribArray(attrib);
    glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), 0);

    attrib = _shader->getAttributeLocation("color");
    glEnableVertexAttribArray(attrib);
    glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));

}

unsigned char* Floor::getMap() {
    return _map;
}

void Floor::draw(glm::mat4 viewProjectionMatrix) {
    _shader->use();
    glUniformMatrix4fv(_shader->getUniformLocation("transformMatrix"), 1, GL_FALSE, glm::value_ptr(viewProjectionMatrix));
    glBindVertexArray(_vertexArrayObject);
    glDrawElements(GL_TRIANGLES, _numFilled*6*6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(_lineVertexArrayObject);
    glDrawElements(GL_LINES, _numFilled*24, GL_UNSIGNED_INT, 0);
}