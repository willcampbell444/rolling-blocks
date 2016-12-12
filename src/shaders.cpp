#include <shaders.h>

Shaders::~Shaders() {
    glDeleteProgram(_program);
    for (GLuint shader: _shaders) {
        glDeleteShader(shader);
    }
}

bool Shaders::loadShader(GLenum shaderType, const char* filename) {
    const char* shaderSource = loadFile(filename);

    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);
    _shaders.push_back(shader);
    
    delete[] shaderSource;

    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    return status == GL_TRUE;
}

bool Shaders::createProgram() {
    _program = glCreateProgram();

    for (GLuint shader: _shaders) {
        glAttachShader(_program, shader);
    }

    glBindFragDataLocation(_program, 0, "outColor");
    glLinkProgram(_program);

    GLint isLinked;
    glGetProgramiv(_program, GL_LINK_STATUS, &isLinked);
    return isLinked == GL_TRUE;
}

void Shaders::use() {
    glUseProgram(_program);
}

GLuint Shaders::getAttributeLocation(const char* name) {
    return glGetAttribLocation(_program, name);
}

GLuint Shaders::getUniformLocation(const char* name) {
    return glGetUniformLocation(_program, name);
}