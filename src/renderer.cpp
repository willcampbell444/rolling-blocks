#include <renderer.h>

Renderer::Renderer() {
    _shader = new Shaders();

    if (!_shader->loadShader(GL_VERTEX_SHADER, "shaders/vertex.glsl")) {
        std::cout << "Vertex Shader Failed To Compile" << std::endl;
    }
    if (!_shader->loadShader(GL_FRAGMENT_SHADER, "shaders/fragment.glsl")) {
        std::cout << "Fragment Shader Failed To Compile" << std::endl;
    }
    if (!_shader->createProgram()) {
        std::cout << "Shader Failed To Link" << std::endl;
    }

    _textShader = new Shaders();
    if (!_textShader->loadShader(GL_VERTEX_SHADER, "shaders/textVertex.glsl")) {
        std::cout << "Text Vertex Shader Failed To Compile" << std::endl;
    }
    if (!_textShader->loadShader(GL_FRAGMENT_SHADER, "shaders/textFragment.glsl")) {
        std::cout << "Text Fragment Shader Failed To Compile" << std::endl;
    }
    if (!_textShader->createProgram()) {
        std::cout << "Text Shader Failed To Link" << std::endl;
    }

    _shader->use();

    float vertices[36*6] = {
        -0.5,  0.5f,  -0.5, 0.0f, 1.0f, 0.0f,
        -0.5,  0.5f,   0.5, 0.0f, 1.0f, 0.0f,
         0.5,  0.5f,   0.5, 0.0f, 1.0f, 0.0f,
         0.5,  0.5f,   0.5, 0.0f, 1.0f, 0.0f,
         0.5,  0.5f,  -0.5, 0.0f, 1.0f, 0.0f,
        -0.5,  0.5f,  -0.5, 0.0f, 1.0f, 0.0f,

        -0.5, -0.5f,  -0.5, 0.0f, -1.0f, 0.0f,
         0.5, -0.5f,   0.5, 0.0f, -1.0f, 0.0f,
        -0.5, -0.5f,   0.5, 0.0f, -1.0f, 0.0f,
         0.5, -0.5f,   0.5, 0.0f, -1.0f, 0.0f,
        -0.5, -0.5f,  -0.5, 0.0f, -1.0f, 0.0f,
         0.5, -0.5f,  -0.5, 0.0f, -1.0f, 0.0f,

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
         0.5,  0.5f,   0.5, 0.0f, 0.0f, 1.0f,
        -0.5,  0.5f,   0.5, 0.0f, 0.0f, 1.0f,
         0.5,  0.5f,   0.5, 0.0f, 0.0f, 1.0f,
        -0.5, -0.5f,   0.5, 0.0f, 0.0f, 1.0f,
         0.5, -0.5f,   0.5, 0.0f, 0.0f, 1.0f
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
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    if (FT_Init_FreeType(&_freetype)) {
        std::cout << "Could not init FreeType Library" << std::endl;
    }

    if (FT_New_Face(_freetype, "Mohave-Bold.ttf", 0, &_font)) {
        std::cout << "Failed to load font" << std::endl;  
    }
    FT_Set_Pixel_Sizes(_font, 0, 48);

    for (GLubyte i = 0; i < 128; i++) {
        if (FT_Load_Char(_font, i, FT_LOAD_RENDER)) {
            std::cout << "Failed loading char " << i << std::endl;
            continue;
        }

        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            (GLuint)_font->glyph->bitmap.width,
            (GLuint)_font->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            _font->glyph->bitmap.buffer
        );
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Character character = {
            texture,
            glm::ivec2(_font->glyph->bitmap.width, _font->glyph->bitmap.rows),
            glm::ivec2(_font->glyph->bitmap_left, _font->glyph->bitmap_top),
            (GLuint)_font->glyph->advance.x
        };
        _characters[i] = character;
    }

    FT_Done_Face(_font);
    FT_Done_FreeType(_freetype);

    _textShader->use();
    _textProjection = glm::ortho(0.0f, (float)GLOBAL::WINDOW_WIDTH, 0.0f, (float)GLOBAL::WINDOW_HEIGHT);
    // _textProjection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);
    glUniformMatrix4fv(
        _textShader->getUniformLocation("projection"), 
        1,
        GL_FALSE,
        glm::value_ptr(_textProjection)
    );

    glGenVertexArrays(1, &_textVAO);
    glBindVertexArray(_textVAO);

    glGenBuffers(1, &_textVBO);
    glBindBuffer(GL_ARRAY_BUFFER, _textVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*6*2*2, NULL, GL_DYNAMIC_DRAW);

    attrib = _textShader->getAttributeLocation("vertex");
    glEnableVertexAttribArray(attrib);
    glVertexAttribPointer(attrib, 2, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), 0);

    attrib = _textShader->getAttributeLocation("texCoord");
    glEnableVertexAttribArray(attrib);
    glVertexAttribPointer(attrib, 2, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), (void*)(2*sizeof(GLfloat)));
}

void Renderer::drawText(std::string text, float x, float y, float scale) {
    _textShader->use();

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(_textVAO);

    for (char c: text) {
        Character character = _characters[c];

        float xPos = x + character.bearing.x*scale;
        float yPos = y + (character.size.y - character.bearing.y)*scale;

        float w = character.size.x*scale;
        float h = character.size.y*scale;

        GLfloat vertices[6*2*2] = {
            xPos, yPos + h,     0, 0,
            xPos, yPos,         0, 1,
            xPos + w, yPos,     1, 1,

            xPos, yPos + h,     0, 0,
            xPos + w, yPos,     1, 1,
            xPos + w, yPos + h, 1, 0,
        };

        glBindTexture(GL_TEXTURE_2D, character.textureID);
        glBindBuffer(GL_ARRAY_BUFFER, _textVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDrawArrays(GL_TRIANGLES, 0, 6);
        x += (character.advance >> 6) * scale;
    }
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

void Renderer::drawBoxFrame(glm::mat4 viewProjectionMatrix, float x, float y, float z, glm::vec3 color) {
    _shader->use();
    glUniform1i(_shader->getUniformLocation("useLighting"), true);
    glUniform3f(_shader->getUniformLocation("color"), color.r, color.g, color.b);
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
    glUniform3f(
        _shader->getUniformLocation("color"), 
        color.r, 
        color.g, 
        color.b
    );
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

void Renderer::drawFloorTileFrame(glm::mat4 viewProjectionMatrix, float x, float z, glm::vec3 color) {
    _shader->use();
    glUniform1i(_shader->getUniformLocation("useLighting"), true);
    glUniform3f(
        _shader->getUniformLocation("color"), 
        color.r, 
        color.g, 
        color.b
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