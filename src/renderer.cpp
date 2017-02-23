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
    _textShader->use();
    glUniform1i(_textShader->getUniformLocation("character"), 0);

    _dimShader = new Shaders();
    if (!_dimShader->loadShader(GL_VERTEX_SHADER, "shaders/dimVertex.glsl")) {
        std::cout << "Dim Vertex Shader Failed To Compile" << std::endl;
    }
    if (!_dimShader->loadShader(GL_FRAGMENT_SHADER, "shaders/dimFragment.glsl")) {
        std::cout << "Dim Fragment Shader Failed To Compile" << std::endl;
    }
    if (!_dimShader->createProgram()) {
        std::cout << "Dim Shader Failed To Link" << std::endl;
    }

    _squareShader = new Shaders();
    if (!_squareShader->loadShader(GL_VERTEX_SHADER, "shaders/squareVertex.glsl")) {
        std::cout << "Square Vertex Shader Failed To Compile" << std::endl;
    }
    if (!_squareShader->loadShader(GL_FRAGMENT_SHADER, "shaders/squareFragment.glsl")) {
        std::cout << "Square Fragment Shader Failed To Compile" << std::endl;
    }
    if (!_squareShader->createProgram()) {
        std::cout << "Square Shader Failed To Link" << std::endl;
    }

    _shader->use();

    // only for non mobile:
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

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

    glGenBuffers(1, &_boxVBO);
    glBindBuffer(GL_ARRAY_BUFFER, _boxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*36*6, vertices, GL_STATIC_DRAW);
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    if (FT_Init_FreeType(&_freetype)) {
        std::cout << "Could not init FreeType Library" << std::endl;
    }

    FT_Open_Args args;
    args.flags = FT_OPEN_MEMORY;
    args.memory_base = (const FT_Byte*)loadFile("assets/Mohave-Bold.ttf");
    args.memory_size = fileSize("assets/Mohave-Bold.ttf");

    if (FT_Open_Face(_freetype, &args, 0, &_font)) {
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
            GL_LUMINANCE,
            (GLuint)_font->glyph->bitmap.width,
            (GLuint)_font->glyph->bitmap.rows,
            0,
            GL_LUMINANCE,
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

    // small text
    FT_Set_Pixel_Sizes(_font, 0, 32);

    for (GLubyte i = 0; i < 128; i++) {
        if (FT_Load_Char(_font, i, FT_LOAD_RENDER)) {
            std::cout << "Failed loading small char " << i << std::endl;
            continue;
        }

        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_LUMINANCE,
            (GLuint)_font->glyph->bitmap.width,
            (GLuint)_font->glyph->bitmap.rows,
            0,
            GL_LUMINANCE,
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
        _smallCharacters[i] = character;
    }

    FT_Done_Face(_font);
    delete[] args.memory_base;
    FT_Done_FreeType(_freetype);

    _textProjection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);
    _textShader->use();
    glUniformMatrix4fv(
        _textShader->getUniformLocation("projection"), 
        1,
        GL_FALSE,
        glm::value_ptr(_textProjection)
    );
    _squareShader->use();
    glUniformMatrix4fv(
        _squareShader->getUniformLocation("projection"), 
        1,
        GL_FALSE,
        glm::value_ptr(_textProjection)
    );

    glGenBuffers(1, &_textVBO);
    glBindBuffer(GL_ARRAY_BUFFER, _textVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*6*3*2, NULL, GL_DYNAMIC_DRAW);

    GLfloat dimVertices[2*6] = {
        -1.0f, -1.0f,
         1.0f,  1.0f,
        -1.0f,  1.0f,
         1.0f,  1.0f,
        -1.0f, -1.0f,
         1.0f, -1.0f
    };

    glGenBuffers(1, &_dimVBO);
    glBindBuffer(GL_ARRAY_BUFFER, _dimVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*2*6, dimVertices, GL_STATIC_DRAW);

    glGenBuffers(1, &_squareVBO);
    glBindBuffer(GL_ARRAY_BUFFER, _squareVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*6*2, NULL, GL_DYNAMIC_DRAW);
}

void Renderer::loadTextBuffer() {
    glBindBuffer(GL_ARRAY_BUFFER, _textVBO);

    GLuint attrib = _textShader->getAttributeLocation("vertex");
    glEnableVertexAttribArray(attrib);
    glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), 0);

    attrib = _textShader->getAttributeLocation("texCoord");
    glEnableVertexAttribArray(attrib);
    glVertexAttribPointer(attrib, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));
}

void Renderer::loadBoxBuffer() {
    glBindBuffer(GL_ARRAY_BUFFER, _boxVBO);

    GLuint attrib = _shader->getAttributeLocation("position");
    glEnableVertexAttribArray(attrib);
    glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), 0);

    attrib = _shader->getAttributeLocation("normal");
    glEnableVertexAttribArray(attrib);
    glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));
}

void Renderer::loadDimBuffer() {
    glBindBuffer(GL_ARRAY_BUFFER, _dimVBO);

    GLuint attrib = _dimShader->getAttributeLocation("position");
    glEnableVertexAttribArray(attrib);
    glVertexAttribPointer(attrib, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GLfloat), 0);
}

void Renderer::loadSquareBuffer() {
    glBindBuffer(GL_ARRAY_BUFFER, _squareVBO);

    GLuint attrib = _squareShader->getAttributeLocation("position");
    glEnableVertexAttribArray(attrib);
    glVertexAttribPointer(attrib, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GLfloat), 0);
}

void Renderer::resize(int w, int h) {
    _screenWidth = w;
    _screenHeight = h;

    _textProjection = glm::ortho(0.0f, (float)_screenWidth, 0.0f, (float)_screenHeight, -1.0f, 1.0f);
    _textShader->use();
    glUniformMatrix4fv(
        _textShader->getUniformLocation("projection"), 
        1,
        GL_FALSE,
        glm::value_ptr(_textProjection)
    );
    _squareShader->use();
    glUniformMatrix4fv(
        _squareShader->getUniformLocation("projection"), 
        1,
        GL_FALSE,
        glm::value_ptr(_textProjection)
    );
}

void Renderer::drawText(std::string text, float x, float y, float scale, glm::vec3 color) {
    glDisable(GL_DEPTH_TEST);
    drawTextShadow(text, x, y, scale, GLOBAL::TEXT_SHADOW);

    _textShader->use();
    glUniform4f(_textShader->getUniformLocation("color"), color.r, color.g, color.b, 1.0f);

    glActiveTexture(GL_TEXTURE0);
    loadTextBuffer();

    Character character;

    bool small = scale == -1;
    if (small) {
        scale = 1;
    }

    for (char c: text) {
        if (small) {
            character = _smallCharacters[c];
        } else {
            character = _characters[c];
        }

        float xPos = x + character.bearing.x*scale;
        float yPos = y - (character.size.y - character.bearing.y)*scale;

        float w = character.size.x*scale;
        float h = character.size.y*scale;

        GLfloat vertices[6*3*2] = {
            xPos, yPos + h, -0.1,     0, 0,
            xPos, yPos, -0.1,         0, 1,
            xPos + w, yPos, -0.1,     1, 1,

            xPos, yPos + h, -0.1,     0, 0,
            xPos + w, yPos, -0.1,     1, 1,
            xPos + w, yPos + h, -0.1, 1, 0,
        };

        glBindTexture(GL_TEXTURE_2D, character.textureID);
        glBindBuffer(GL_ARRAY_BUFFER, _textVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDrawArrays(GL_TRIANGLES, 0, 6);
        x += (character.advance >> 6) * scale;
    }
    glEnable(GL_DEPTH_TEST);
}

void Renderer::drawTextShadow(std::string text, float x, float y, float scale, glm::vec3 color) {
    _textShader->use();
    glUniform4f(_textShader->getUniformLocation("color"), color.r, color.g, color.b, 1.0f);

    glActiveTexture(GL_TEXTURE0);
    loadTextBuffer();

    Character character;

    bool small = scale == -1;
    if (small) {
        scale = 1;
    }

    for (char c: text) {
        if (small) {
            character = _smallCharacters[c];
        } else {
            character = _characters[c];
        }

        float xPos = x + character.bearing.x*scale;
        float yPos = y - (character.size.y - character.bearing.y)*scale;

        float w = character.size.x*scale;
        float h = character.size.y*scale;

        float offset = scale*2;
        if (small) {
            offset = offset/2;
        }

        GLfloat vertices[6*3*2] = {
            xPos + offset,            yPos - offset + h,    -0.2f,  0, 0,
            xPos + offset,            yPos - offset, -0.2f,  0, 1,
            xPos + w + offset, yPos - offset, -0.2f,  1, 1,

            xPos + offset,            yPos - offset + h,    -0.2f,  0, 0,
            xPos + w + offset, yPos - offset, -0.2f,  1, 1,
            xPos + w + offset, yPos - offset + h,    -0.2f,  1, 0,
        };
        glBindTexture(GL_TEXTURE_2D, character.textureID);
        glBindBuffer(GL_ARRAY_BUFFER, _textVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDrawArrays(GL_TRIANGLES, 0, 6);
        x += (character.advance >> 6) * scale;
    }
}

void Renderer::drawTextRight(std::string text, float x, float y, float scale, glm::vec3 color) {
    bool small = scale == -1;
    if (small) {
        scale = 1;
    }
    x = _screenWidth-x;

    for (char c: text) {
        if (small) {
            x -= (_smallCharacters[c].advance >> 6) * scale;
        } else {
            x -= (_characters[c].advance >> 6) * scale;
        }
    }
    if (small) {
        drawText(text, x, y, -1, GLOBAL::TEXT_COLOR);
    } else {
        drawText(text, x, y, scale, GLOBAL::TEXT_COLOR);
    }
}

void Renderer::drawTextCenter(std::string text, float x, float y, float scale, glm::vec3 color) {
    bool small = scale == -1;
    if (small) {
        scale = 1;
    }

    float w = 0;
    for (char c: text) {
        if (small) {
            w += (_smallCharacters[c].advance >> 6) * scale;
        } else {
            w += (_characters[c].advance >> 6) * scale;
        }
    }
    if (small) {
        drawText(text, x + _screenWidth/2.0f - (w/2.0f), y, -1, GLOBAL::TEXT_COLOR);
    } else {
        drawText(text, x + _screenWidth/2.0f - (w/2.0f), y, scale, GLOBAL::TEXT_COLOR);
    }
}


void Renderer::drawTextTop(std::string text, float x, float y, float scale, glm::vec3 color) {
    drawText(text, x, _screenHeight-y, scale, color);
}

void Renderer::drawTextRightTop(std::string text, float x, float y, float scale, glm::vec3 color) {
    drawTextRight(text, x, _screenHeight-y, scale, color);
}

void Renderer::drawTextCenterTop(std::string text, float x, float y, float scale, glm::vec3 color) {
    drawTextCenter(text, x, _screenHeight-y, scale, color);
}

void Renderer::drawSquare(float left, float right, float bottom, float top, glm::vec3 color, float trans) {
    glDisable(GL_DEPTH_TEST);
    _squareShader->use();
    glUniform4f(_squareShader->getUniformLocation("color"), color.r, color.g, color.b, trans);

    GLfloat vertices[2*6] = {
        right, top,
        left, top,
        left, bottom,

        left, bottom,
        right, bottom,
        right, top
    };

    loadSquareBuffer();
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    // MAYBE LOAD SQUARE BUFFER AGAIN HERE

    glDrawArrays(GL_TRIANGLES, 0, 6);
    glEnable(GL_DEPTH_TEST);
}

void Renderer::dim(float amount) {
    glDisable(GL_DEPTH_TEST);
    _dimShader->use();

    glUniform1f(_dimShader->getUniformLocation("amount"), amount);

    loadDimBuffer();
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glEnable(GL_DEPTH_TEST);
}

Shaders* Renderer::getShader() {
    return _shader;
}

void Renderer::drawBox(glm::mat4 viewProjectionMatrix, float x, float y, float z, glm::vec3 color) {
    _shader->use();
    model = glm::translate(glm::mat4(1.0f), glm::vec3(x, y+0.5f, z));
    model = glm::scale(model, glm::vec3(GLOBAL::BLOCK_WIDTH));

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
    glUniform3f(_shader->getUniformLocation("color"), color.r, color.g, color.b);
    loadBoxBuffer();
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Renderer::drawBoxFrame(glm::mat4 viewProjectionMatrix, float x, float y, float z, glm::vec3 color) {
    _shader->use();
    glUniform1i(_shader->getUniformLocation("useLighting"), true);
    glUniform3f(_shader->getUniformLocation("color"), color.r, color.g, color.b);
    loadBoxBuffer();
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
    model = glm::translate(glm::mat4(1.0f), center);
    model = glm::rotate(model, glm::radians(angle), axis);
    model = glm::translate(model, -center);
    model = glm::translate(model, glm::vec3(x, y+0.5f, z));
    model = glm::scale(model, glm::vec3(GLOBAL::BLOCK_WIDTH));

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
    glUniform3f(_shader->getUniformLocation("color"), color.r, color.g, color.b);
    loadBoxBuffer();
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Renderer::drawFloorTile(glm::mat4 viewProjectionMatrix, float x, float z) {
    _shader->use();
    model = glm::translate(glm::mat4(1.0f), glm::vec3(x, -GLOBAL::GAP, z));
    model = glm::scale(model, glm::vec3(
        GLOBAL::BLOCK_WIDTH, 
        GLOBAL::FLOOR_HEIGHT-2*GLOBAL::GAP, 
        GLOBAL::BLOCK_WIDTH)
    );
    model = glm::translate(model, glm::vec3(0, -0.5, 0));

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

    glUniform3f(
        _shader->getUniformLocation("color"), 
        GLOBAL::FLOOR_COLOR.r, 
        GLOBAL::FLOOR_COLOR.g, 
        GLOBAL::FLOOR_COLOR.b
    );
    loadBoxBuffer();
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Renderer::drawFloorTileFrame(glm::mat4 viewProjectionMatrix, float x, float z, glm::vec3 color) {
    _shader->use();
    glUniform3f(
        _shader->getUniformLocation("color"), 
        color.r, 
        color.g, 
        color.b
    );
    loadBoxBuffer();

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
    model = glm::translate(glm::mat4(1.0f), glm::vec3(x, -GLOBAL::GAP*5, z));
    model = glm::scale(model, glm::vec3(
        GLOBAL::BLOCK_WIDTH, 
        GLOBAL::FLOOR_HEIGHT-6*GLOBAL::GAP, 
        GLOBAL::BLOCK_WIDTH)
    );
    model = glm::translate(model, glm::vec3(0, -0.5, 0));

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

    glUniform3f(
        _shader->getUniformLocation("color"), 
        GLOBAL::VICTORY_COLOR.x, 
        GLOBAL::VICTORY_COLOR.y, 
        GLOBAL::VICTORY_COLOR.z
    );
    loadBoxBuffer();
    glDrawArrays(GL_TRIANGLES, 0, 36);
}