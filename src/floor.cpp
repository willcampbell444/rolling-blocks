#include <floor.h>

const float GAP = 0.05f;
const float BOTTOM = -2.0f;

Floor::Floor(Shaders* shader, int width, int length) {
    _width = width;
    _length = length;
    _shader = shader;
    float* vertices = new float[_width*length*8*6];
    float* lineVertices = new float[_width*length*8*6];

    int count = 0;

    for (float i = -(width)/2.0f; i < (width)/2.0f; i += 1.0f) {
        for (float j = -(length)/2.0f; j < (length)/2.0f; j += 1.0f) {
            vertices[ count ]  = i+GAP;
            vertices[count+1]  = -GAP;
            vertices[count+2]  = j+GAP;

            vertices[count+3]  = 0.752941;
            vertices[count+4]  = 0.772549;
            vertices[count+5]  = 0.8078431;

            vertices[count+6]  = i+1-GAP;
            vertices[count+7]  = -GAP;
            vertices[count+8]  = j+GAP;

            vertices[count+9]  = 0.752941;
            vertices[count+10]  = 0.772549;
            vertices[count+11]  = 0.8078431;

            vertices[count+12]  = i+1-GAP;
            vertices[count+13]  = -GAP;
            vertices[count+14]  = j+1-GAP;

            vertices[count+15]  = 0.752941;
            vertices[count+16]  = 0.772549;
            vertices[count+17]  = 0.8078431;

            vertices[count+18]  = i+GAP;
            vertices[count+19] = -GAP;
            vertices[count+20] = j+1-GAP;

            vertices[count+21]  = 0.752941;
            vertices[count+22]  = 0.772549;
            vertices[count+23]  = 0.8078431;

            vertices[count+24] = i+GAP;
            vertices[count+25] = BOTTOM+GAP;
            vertices[count+26] = j+GAP;


            vertices[count+27]  = 0.168627;
            vertices[count+28]  = 0.188235;
            vertices[count+29]  = 0.23137;

            vertices[count+30] = i+1-GAP;
            vertices[count+31] = BOTTOM+GAP;
            vertices[count+32] = j+GAP;

            vertices[count+33]  = 0.168627;
            vertices[count+34]  = 0.188235;
            vertices[count+35]  = 0.23137;

            vertices[count+36] = i+1-GAP;
            vertices[count+37] = BOTTOM+GAP;
            vertices[count+38] = j+1-GAP;

            vertices[count+39]  = 0.168627;
            vertices[count+40]  = 0.188235;
            vertices[count+41]  = 0.23137;

            vertices[count+42] = i+GAP;
            vertices[count+43] = BOTTOM+GAP;
            vertices[count+44] = j+1-GAP;

            vertices[count+45]  = 0.168627;
            vertices[count+46]  = 0.188235;
            vertices[count+47]  = 0.23137;

            count += 48;
        }
    }

    count = 0;

    for (float i = -(width)/2.0f; i < (width)/2.0f; i += 1.0f) {
        for (float j = -(length)/2.0f; j < (length)/2.0f; j += 1.0f) {
            lineVertices[ count ]  = i+GAP;
            lineVertices[count+1]  = -GAP;
            lineVertices[count+2]  = j+GAP;

            lineVertices[count+3]  = 1;
            lineVertices[count+4]  = 1;
            lineVertices[count+5]  = 1;

            lineVertices[count+6]  = i+1-GAP;
            lineVertices[count+7]  = -GAP;
            lineVertices[count+8]  = j+GAP;

            lineVertices[count+9]  = 1;
            lineVertices[count+10]  = 1;
            lineVertices[count+11]  = 1;

            lineVertices[count+12]  = i+1-GAP;
            lineVertices[count+13]  = -GAP;
            lineVertices[count+14]  = j+1-GAP;

            lineVertices[count+15]  = 1;
            lineVertices[count+16]  = 1;
            lineVertices[count+17]  = 1;

            lineVertices[count+18]  = i+GAP;
            lineVertices[count+19] = -GAP;
            lineVertices[count+20] = j+1-GAP;

            lineVertices[count+21]  = 1;
            lineVertices[count+22]  = 1;
            lineVertices[count+23]  = 1;

            lineVertices[count+24] = i+GAP;
            lineVertices[count+25] = BOTTOM+GAP;
            lineVertices[count+26] = j+GAP;

            lineVertices[count+27]  = 0.168627;
            lineVertices[count+28]  = 0.188235;
            lineVertices[count+29]  = 0.23137;

            lineVertices[count+30] = i+1-GAP;
            lineVertices[count+31] = BOTTOM+GAP;
            lineVertices[count+32] = j+GAP;

            lineVertices[count+33]  = 0.168627;
            lineVertices[count+34]  = 0.188235;
            lineVertices[count+35]  = 0.23137;

            lineVertices[count+36] = i+1-GAP;
            lineVertices[count+37] = BOTTOM+GAP;
            lineVertices[count+38] = j+1-GAP;

            lineVertices[count+39]  = 0.168627;
            lineVertices[count+40]  = 0.188235;
            lineVertices[count+41]  = 0.23137;

            lineVertices[count+42] = i+GAP;
            lineVertices[count+43] = BOTTOM+GAP;
            lineVertices[count+44] = j+1-GAP;

            lineVertices[count+45]  = 0.168627;
            lineVertices[count+46]  = 0.188235;
            lineVertices[count+47]  = 0.23137;

            count += 48;
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

    GLuint* elements = new GLuint[_width*_length*6*6];

    for (int x = 0; x < _width*_length; x++) {
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

    GLuint* lineElements = new GLuint[_width*_length*24];

    for (int x = 0; x < _width*_length; x++) {
        for (int y = 0; y < 24; y++) {
            lineElements[(x*24)+y] = (x*8)+lineCube[y];
        }
    }

    glGenVertexArrays(1, &_vertexArrayObject);
    glBindVertexArray(_vertexArrayObject);

    glGenBuffers(1, &_elementBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4*_width*_length*6*6, elements, GL_STATIC_DRAW);

    delete elements;

    glGenBuffers(1, &_vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, 4*_width*length*8*6, vertices, GL_STATIC_DRAW);

    delete vertices;

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
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4*_width*_length*24, lineElements, GL_STATIC_DRAW);

    delete lineElements;

    glGenBuffers(1, &_lineVertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, _lineVertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, 4*_width*length*8*6, lineVertices, GL_STATIC_DRAW);
    
    delete lineVertices;

    attrib = _shader->getAttributeLocation("position");
    glEnableVertexAttribArray(attrib);
    glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), 0);

    attrib = _shader->getAttributeLocation("color");
    glEnableVertexAttribArray(attrib);
    glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));
}

Floor::~Floor() {
    glDeleteBuffers(1, &_vertexBufferObject);
    glDeleteBuffers(1, &_elementBufferObject);
    glDeleteVertexArrays(1, &_vertexArrayObject);
}

void Floor::create() {
} 

void Floor::draw(glm::mat4 viewProjectionMatrix) {
    _shader->use();
    glUniformMatrix4fv(_shader->getUniformLocation("transformMatrix"), 1, GL_FALSE, glm::value_ptr(viewProjectionMatrix));
    glBindVertexArray(_vertexArrayObject);
    glDrawElements(GL_TRIANGLES, _width*_length*6*6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(_lineVertexArrayObject);
    glDrawElements(GL_LINES, _width*_length*24, GL_UNSIGNED_INT, 0);
}