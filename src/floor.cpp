#include <floor.h>

Floor::Floor(Shaders* shader) {
    _shader = shader;

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

    glBindVertexArray(_vertexArrayObject);

    GLuint vertexBufferObject;
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*36*6, vertices, GL_STATIC_DRAW);

    GLuint attrib = _shader->getAttributeLocation("position");
    glEnableVertexAttribArray(attrib);
    glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), 0);

    attrib = _shader->getAttributeLocation("normal");
    glEnableVertexAttribArray(attrib);
    glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));
}

Floor::~Floor() {
    glDeleteVertexArrays(1, &_vertexArrayObject);
}

void Floor::create(int width, int length, unsigned char* tiles) {
    _width = width;
    _length = length;

    _map = tiles;
}

unsigned char* Floor::getMap() {
    return _map;
}

void Floor::draw(glm::mat4 viewProjectionMatrix) {
    _shader->use();

    int count = 0;
    glm::mat4 model;
    for (float i = -(_width)/2.0f; i < (_width)/2.0f; i += 1.0f) {
        for (float j = -(_length)/2.0f; j < (_length)/2.0f; j += 1.0f) {
            if (_map[count] == 1) {
                model = (
                    glm::translate(
                        glm::mat4(1.0f), 
                        glm::vec3(
                            i+0.5f,
                            -GLOBAL::FLOOR_HEIGHT/2.0f,
                            j+0.5f
                        )
                    )
                    * glm::scale(glm::mat4(1.0f), glm::vec3((GLOBAL::BLOCK_WIDTH), GLOBAL::FLOOR_HEIGHT-(GLOBAL::GAP*2), (GLOBAL::BLOCK_WIDTH)))
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
                glBindVertexArray(_vertexArrayObject);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            } else if (_map[count] == 2) {
                model = (
                    glm::translate(
                        glm::mat4(1.0f), 
                        glm::vec3(
                            i+0.5f,
                            -GLOBAL::GAP*5,
                            j+0.5f
                        )
                    )
                    * glm::scale(glm::mat4(1.0f), glm::vec3((GLOBAL::BLOCK_WIDTH), GLOBAL::FLOOR_HEIGHT-(GLOBAL::GAP*6), (GLOBAL::BLOCK_WIDTH)))
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
                glBindVertexArray(_vertexArrayObject);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
            count += 1;
        }
    }
}