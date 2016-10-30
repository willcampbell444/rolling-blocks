#include <renderer.h>

Renderer::Renderer() {
    _shader = new Shaders();

    if (!_shader->loadShader(GL_VERTEX_SHADER, "shaders/vertex.glsl")) {
        std::cout << "Vertex Shader Failed To Compile" << std::endl;
    }
    if (!_shader->loadShader(GL_FRAGMENT_SHADER, "shaders/fragment.glsl")) {
        std::cout << "Fragment Shader Failed To Compile" << std::endl;
    }
    _shader->createProgram();

    _shader->use();

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

    glGenVertexArrays(1, &_vertexArrayObject);
    glBindVertexArray(_vertexArrayObject);

    GLuint vertexBufferObject;
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*36*6, vertices, GL_STATIC_DRAW);

    GLuint attrib = _shader->getAttributeLocation("position");
    glEnableVertexAttribArray(attrib);
    glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), 0);

    attrib = _shader->getAttributeLocation("normal");
    glEnableVertexAttribArray(attrib);
    glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));
}

Shaders* Renderer::getShader() {
    return _shader;
}

void Renderer::drawBox(glm::mat4 viewProjectionMatrix, float x, float y, float z, glm::vec3 color) {
    _shader->use();
    model = (
        glm::translate(glm::mat4(1.0f), glm::vec3(x, y+0.5f, z))
        * glm::scale(glm::mat4(1.0f), glm::vec3(GLOBAL::BLOCK_WIDTH))
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
    glUniform3f(_shader->getUniformLocation("color"), color.r, color.g, color.b);
    glBindVertexArray(_vertexArrayObject);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Renderer::drawBoxFrame(glm::mat4 viewProjectionMatrix, float x, float y, float z) {
    _shader->use();
    glUniform1i(_shader->getUniformLocation("useLighting"), true);
    glUniform3f(_shader->getUniformLocation("color"), GLOBAL::FRAME_COLOR.r, GLOBAL::FRAME_COLOR.g, GLOBAL::FRAME_COLOR.b);
    glBindVertexArray(_vertexArrayObject);
    float dif = 0.5f-GLOBAL::GAP;

    model = (
        glm::translate(glm::mat4(1.0f), glm::vec3(x-dif, y+0.5f, z-dif))
        * glm::scale(glm::mat4(1.0f), glm::vec3(GLOBAL::GAP*2, 1, GLOBAL::GAP*2))
    );
    glUniformMatrix4fv(_shader->getUniformLocation("transformMatrix"), 1, GL_FALSE, glm::value_ptr(viewProjectionMatrix*model));
    glUniformMatrix4fv(_shader->getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    model = (
        glm::translate(glm::mat4(1.0f), glm::vec3(x+dif, y+0.5f, z-dif))
        * glm::scale(glm::mat4(1.0f), glm::vec3(GLOBAL::GAP*2, 1, GLOBAL::GAP*2))
    );
    glUniformMatrix4fv(_shader->getUniformLocation("transformMatrix"), 1, GL_FALSE, glm::value_ptr(viewProjectionMatrix*model));
    glUniformMatrix4fv(_shader->getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    model = (
        glm::translate(glm::mat4(1.0f), glm::vec3(x+dif, y+0.5f, z+dif))
        * glm::scale(glm::mat4(1.0f), glm::vec3(GLOBAL::GAP*2, 1, GLOBAL::GAP*2))
    );
    glUniformMatrix4fv(_shader->getUniformLocation("transformMatrix"), 1, GL_FALSE, glm::value_ptr(viewProjectionMatrix*model));
    glUniformMatrix4fv(_shader->getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    model = (
        glm::translate(glm::mat4(1.0f), glm::vec3(x-dif, y+0.5f, z+dif))
        * glm::scale(glm::mat4(1.0f), glm::vec3(GLOBAL::GAP*2, 1, GLOBAL::GAP*2))
    );
    glUniformMatrix4fv(_shader->getUniformLocation("transformMatrix"), 1, GL_FALSE, glm::value_ptr(viewProjectionMatrix*model));
    glUniformMatrix4fv(_shader->getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 0, 36);



    model = (
        glm::translate(glm::mat4(1.0f), glm::vec3(x, y+0.5f+dif, z+dif))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1, GLOBAL::GAP*2, GLOBAL::GAP*2))
    );
    glUniformMatrix4fv(_shader->getUniformLocation("transformMatrix"), 1, GL_FALSE, glm::value_ptr(viewProjectionMatrix*model));
    glUniformMatrix4fv(_shader->getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    model = (
        glm::translate(glm::mat4(1.0f), glm::vec3(x, y+0.5f-dif, z+dif))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1, GLOBAL::GAP*2, GLOBAL::GAP*2))
    );
    glUniformMatrix4fv(_shader->getUniformLocation("transformMatrix"), 1, GL_FALSE, glm::value_ptr(viewProjectionMatrix*model));
    glUniformMatrix4fv(_shader->getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    model = (
        glm::translate(glm::mat4(1.0f), glm::vec3(x, y+0.5f-dif, z-dif))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1, GLOBAL::GAP*2, GLOBAL::GAP*2))
    );
    glUniformMatrix4fv(_shader->getUniformLocation("transformMatrix"), 1, GL_FALSE, glm::value_ptr(viewProjectionMatrix*model));
    glUniformMatrix4fv(_shader->getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    model = (
        glm::translate(glm::mat4(1.0f), glm::vec3(x, y+0.5f+dif, z-dif))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1, GLOBAL::GAP*2, GLOBAL::GAP*2))
    );
    glUniformMatrix4fv(_shader->getUniformLocation("transformMatrix"), 1, GL_FALSE, glm::value_ptr(viewProjectionMatrix*model));
    glUniformMatrix4fv(_shader->getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 0, 36);



    model = (
        glm::translate(glm::mat4(1.0f), glm::vec3(x+dif, y+0.5f+dif, z))
        * glm::scale(glm::mat4(1.0f), glm::vec3(GLOBAL::GAP*2, GLOBAL::GAP*2, 1))
    );
    glUniformMatrix4fv(_shader->getUniformLocation("transformMatrix"), 1, GL_FALSE, glm::value_ptr(viewProjectionMatrix*model));
    glUniformMatrix4fv(_shader->getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    model = (
        glm::translate(glm::mat4(1.0f), glm::vec3(x-dif, y+0.5f+dif, z))
        * glm::scale(glm::mat4(1.0f), glm::vec3(GLOBAL::GAP*2, GLOBAL::GAP*2, 1))
    );
    glUniformMatrix4fv(_shader->getUniformLocation("transformMatrix"), 1, GL_FALSE, glm::value_ptr(viewProjectionMatrix*model));
    glUniformMatrix4fv(_shader->getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    model = (
        glm::translate(glm::mat4(1.0f), glm::vec3(x+dif, y+0.5f-dif, z))
        * glm::scale(glm::mat4(1.0f), glm::vec3(GLOBAL::GAP*2, GLOBAL::GAP*2, 1))
    );
    glUniformMatrix4fv(_shader->getUniformLocation("transformMatrix"), 1, GL_FALSE, glm::value_ptr(viewProjectionMatrix*model));
    glUniformMatrix4fv(_shader->getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    model = (
        glm::translate(glm::mat4(1.0f), glm::vec3(x-dif, y+0.5f-dif, z))
        * glm::scale(glm::mat4(1.0f), glm::vec3(GLOBAL::GAP*2, GLOBAL::GAP*2, 1))
    );
    glUniformMatrix4fv(_shader->getUniformLocation("transformMatrix"), 1, GL_FALSE, glm::value_ptr(viewProjectionMatrix*model));
    glUniformMatrix4fv(_shader->getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Renderer::drawRotatedBox(glm::mat4 viewProjectionMatrix, float x, float y, float z, float angle, glm::vec3 center, glm::vec3 axis, glm::vec3 color) {
    _shader->use();
    model = (
        glm::translate(glm::mat4(1.0f), center)
        * glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis)
        * glm::translate(glm::mat4(1.0f), -center)
        * glm::translate(glm::mat4(1.0f), glm::vec3(x, y+0.5f, z))
        * glm::scale(glm::mat4(1.0f), glm::vec3(GLOBAL::BLOCK_WIDTH))
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
    glBindVertexArray(_vertexArrayObject);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Renderer::drawFloorTile(glm::mat4 viewProjectionMatrix, float x, float z) {
    _shader->use();
    model = (
        glm::translate(glm::mat4(1.0f), glm::vec3(x, -GLOBAL::GAP, z))
        * glm::scale(glm::mat4(1.0f), glm::vec3(
        	GLOBAL::BLOCK_WIDTH, 
        	GLOBAL::FLOOR_HEIGHT-2*GLOBAL::GAP, 
        	GLOBAL::BLOCK_WIDTH)
        )
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
    glUniform3f(
    	_shader->getUniformLocation("color"), 
    	GLOBAL::FLOOR_COLOR.r, 
    	GLOBAL::FLOOR_COLOR.g, 
    	GLOBAL::FLOOR_COLOR.b
    );
    glBindVertexArray(_vertexArrayObject);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Renderer::drawFloorTileFrame(glm::mat4 viewProjectionMatrix, float x, float z) {
    _shader->use();
    glUniform1i(_shader->getUniformLocation("useLighting"), true);
    glUniform3f(
        _shader->getUniformLocation("color"), 
        GLOBAL::FRAME_COLOR.r, 
        GLOBAL::FRAME_COLOR.g, 
        GLOBAL::FRAME_COLOR.b
    );
    glBindVertexArray(_vertexArrayObject);

    model = (
        glm::translate(glm::mat4(1.0f), glm::vec3(x+(0.5f-GLOBAL::GAP), 0, z+(0.5f-GLOBAL::GAP)))
        * glm::scale(glm::mat4(1.0f), glm::vec3(GLOBAL::GAP*2, GLOBAL::FLOOR_HEIGHT, GLOBAL::GAP*2))
        * glm::translate(glm::mat4(1.0f), glm::vec3(0, -0.5, 0))
    );
    glUniformMatrix4fv(_shader->getUniformLocation("transformMatrix"), 1, GL_FALSE, glm::value_ptr(viewProjectionMatrix*model));
    glUniformMatrix4fv(_shader->getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    model = (
        glm::translate(glm::mat4(1.0f), glm::vec3(x-(0.5f-GLOBAL::GAP), 0, z+(0.5f-GLOBAL::GAP)))
        * glm::scale(glm::mat4(1.0f), glm::vec3(GLOBAL::GAP*2, GLOBAL::FLOOR_HEIGHT, GLOBAL::GAP*2))
        * glm::translate(glm::mat4(1.0f), glm::vec3(0, -0.5, 0))
    );
    glUniformMatrix4fv(_shader->getUniformLocation("transformMatrix"), 1, GL_FALSE, glm::value_ptr(viewProjectionMatrix*model));
    glUniformMatrix4fv(_shader->getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    model = (
        glm::translate(glm::mat4(1.0f), glm::vec3(x-(0.5f-GLOBAL::GAP), 0, z-(0.5f-GLOBAL::GAP)))
        * glm::scale(glm::mat4(1.0f), glm::vec3(GLOBAL::GAP*2, GLOBAL::FLOOR_HEIGHT, GLOBAL::GAP*2))
        * glm::translate(glm::mat4(1.0f), glm::vec3(0, -0.5, 0))
    );
    glUniformMatrix4fv(_shader->getUniformLocation("transformMatrix"), 1, GL_FALSE, glm::value_ptr(viewProjectionMatrix*model));
    glUniformMatrix4fv(_shader->getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    model = (
        glm::translate(glm::mat4(1.0f), glm::vec3(x+(0.5f-GLOBAL::GAP), 0, z-(0.5f-GLOBAL::GAP)))
        * glm::scale(glm::mat4(1.0f), glm::vec3(GLOBAL::GAP*2, GLOBAL::FLOOR_HEIGHT, GLOBAL::GAP*2))
        * glm::translate(glm::mat4(1.0f), glm::vec3(0, -0.5, 0))
    );
    glUniformMatrix4fv(_shader->getUniformLocation("transformMatrix"), 1, GL_FALSE, glm::value_ptr(viewProjectionMatrix*model));
    glUniformMatrix4fv(_shader->getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 0, 36);



    model = (
        glm::translate(glm::mat4(1.0f), glm::vec3(x, 0, z-(0.5f-GLOBAL::GAP)))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1, GLOBAL::GAP*2, GLOBAL::GAP*2))
        * glm::translate(glm::mat4(1.0f), glm::vec3(0, -0.5, 0))
    );
    glUniformMatrix4fv(_shader->getUniformLocation("transformMatrix"), 1, GL_FALSE, glm::value_ptr(viewProjectionMatrix*model));
    glUniformMatrix4fv(_shader->getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    model = (
        glm::translate(glm::mat4(1.0f), glm::vec3(x, 0, z+(0.5f-GLOBAL::GAP)))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1, GLOBAL::GAP*2, GLOBAL::GAP*2))
        * glm::translate(glm::mat4(1.0f), glm::vec3(0, -0.5, 0))
    );
    glUniformMatrix4fv(_shader->getUniformLocation("transformMatrix"), 1, GL_FALSE, glm::value_ptr(viewProjectionMatrix*model));
    glUniformMatrix4fv(_shader->getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    model = (
        glm::translate(glm::mat4(1.0f), glm::vec3(x, -(GLOBAL::FLOOR_HEIGHT)+GLOBAL::GAP*2, z-(0.5f-GLOBAL::GAP)))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1, GLOBAL::GAP*2, GLOBAL::GAP*2))
        * glm::translate(glm::mat4(1.0f), glm::vec3(0, -0.5, 0))
    );
    glUniformMatrix4fv(_shader->getUniformLocation("transformMatrix"), 1, GL_FALSE, glm::value_ptr(viewProjectionMatrix*model));
    glUniformMatrix4fv(_shader->getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    model = (
        glm::translate(glm::mat4(1.0f), glm::vec3(x, -(GLOBAL::FLOOR_HEIGHT)+GLOBAL::GAP*2, z+(0.5f-GLOBAL::GAP)))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1, GLOBAL::GAP*2, GLOBAL::GAP*2))
        * glm::translate(glm::mat4(1.0f), glm::vec3(0, -0.5, 0))
    );
    glUniformMatrix4fv(_shader->getUniformLocation("transformMatrix"), 1, GL_FALSE, glm::value_ptr(viewProjectionMatrix*model));
    glUniformMatrix4fv(_shader->getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 0, 36);



    model = (
        glm::translate(glm::mat4(1.0f), glm::vec3(x-(0.5f-GLOBAL::GAP), 0, z))
        * glm::scale(glm::mat4(1.0f), glm::vec3(GLOBAL::GAP*2, GLOBAL::GAP*2, 1))
        * glm::translate(glm::mat4(1.0f), glm::vec3(0, -0.5, 0))
    );
    glUniformMatrix4fv(_shader->getUniformLocation("transformMatrix"), 1, GL_FALSE, glm::value_ptr(viewProjectionMatrix*model));
    glUniformMatrix4fv(_shader->getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    model = (
        glm::translate(glm::mat4(1.0f), glm::vec3(x+(0.5f-GLOBAL::GAP), 0, z))
        * glm::scale(glm::mat4(1.0f), glm::vec3(GLOBAL::GAP*2, GLOBAL::GAP*2, 1))
        * glm::translate(glm::mat4(1.0f), glm::vec3(0, -0.5, 0))
    );
    glUniformMatrix4fv(_shader->getUniformLocation("transformMatrix"), 1, GL_FALSE, glm::value_ptr(viewProjectionMatrix*model));
    glUniformMatrix4fv(_shader->getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    model = (
        glm::translate(glm::mat4(1.0f), glm::vec3(x-(0.5f-GLOBAL::GAP), -GLOBAL::FLOOR_HEIGHT+GLOBAL::GAP*2, z))
        * glm::scale(glm::mat4(1.0f), glm::vec3(GLOBAL::GAP*2, GLOBAL::GAP*2, 1))
        * glm::translate(glm::mat4(1.0f), glm::vec3(0, -0.5, 0))
    );
    glUniformMatrix4fv(_shader->getUniformLocation("transformMatrix"), 1, GL_FALSE, glm::value_ptr(viewProjectionMatrix*model));
    glUniformMatrix4fv(_shader->getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    model = (
        glm::translate(glm::mat4(1.0f), glm::vec3(x+(0.5f-GLOBAL::GAP), -GLOBAL::FLOOR_HEIGHT+GLOBAL::GAP*2, z))
        * glm::scale(glm::mat4(1.0f), glm::vec3(GLOBAL::GAP*2, GLOBAL::GAP*2, 1))
        * glm::translate(glm::mat4(1.0f), glm::vec3(0, -0.5, 0))
    );
    glUniformMatrix4fv(_shader->getUniformLocation("transformMatrix"), 1, GL_FALSE, glm::value_ptr(viewProjectionMatrix*model));
    glUniformMatrix4fv(_shader->getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Renderer::drawVictoryTile(glm::mat4 viewProjectionMatrix, float x, float z) {
    _shader->use();
    model = (
        glm::translate(glm::mat4(1.0f), glm::vec3(x, -GLOBAL::GAP*5, z))
        * glm::scale(glm::mat4(1.0f), glm::vec3(
        	GLOBAL::BLOCK_WIDTH, 
        	GLOBAL::FLOOR_HEIGHT-6*GLOBAL::GAP, 
        	GLOBAL::BLOCK_WIDTH)
        )
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
    glUniform3f(
    	_shader->getUniformLocation("color"), 
    	GLOBAL::VICTORY_COLOR.x, 
    	GLOBAL::VICTORY_COLOR.y, 
    	GLOBAL::VICTORY_COLOR.z
    );
    glBindVertexArray(_vertexArrayObject);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}