#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include <shaders.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>
#include <unordered_map>
#include <globals.h>
#include <ft2build.h>
#include FT_FREETYPE_H

struct Character {
    GLuint     textureID;
    glm::ivec2 size;
    glm::ivec2 bearing;
    GLuint     advance;
};

class Renderer {
public:
	Renderer();
	Shaders* getShader();
	void drawBox(glm::mat4 viewProjectionMatrix, float x, float y, float z, glm::vec3 color);
	void drawBoxFrame(glm::mat4 viewProjectionMatrix, float x, float y, float z, glm::vec3 color);
	void drawRotatedBox(glm::mat4 viewProjectionMatrix, float x, float y, float z, float angle, glm::vec3 center, glm::vec3 axis, glm::vec3 color);
	void drawFloorTile(glm::mat4 viewProjectionMatrix, float x, float z);
	void drawFloorTileFrame(glm::mat4 viewProjectionMatrix, float x, float z, glm::vec3 color);
	void drawVictoryTile(glm::mat4 viewProjectionMatrix, float x, float z);
    void drawText(std::string text, float x, float y, float scale, glm::vec3 color);
    void drawTextRight(std::string text, float x, float y, float scale, glm::vec3 color);
    void drawTextCenter(std::string text, float x, float y, float scale, glm::vec3 color);
    void drawTextTop(std::string text, float x, float y, float scale, glm::vec3 color);
    void drawTextRightTop(std::string text, float x, float y, float scale, glm::vec3 color);
    void drawTextCenterTop(std::string text, float x, float y, float scale, glm::vec3 color);
    void drawTextShadow(std::string text, float x, float y, float scale, glm::vec3 color);
    void dim(float amount);
    void resize(int w, int h);
private:
    GLuint _vertexArrayObject;
    GLuint _textVBO, _textVAO;
    GLuint _dimVAO;
    glm::mat4 model, _textProjection;
    Shaders* _shader;
    Shaders* _textShader;
    Shaders* _dimShader;
    FT_Library _freetype;
    FT_Face _font;

    int _screenWidth = 800;
    int _screenHeight = 600;

    std::unordered_map<char, Character> _characters;
    std::unordered_map<char, Character> _smallCharacters;
};

#endif