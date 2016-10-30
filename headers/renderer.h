#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include <shaders.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <globals.h>

class Renderer {
public:
	Renderer();
	Shaders* getShader();
	void drawBox(glm::mat4 viewProjectionMatrix, float x, float y, float z, glm::vec3 color);
	void drawBoxFrame(glm::mat4 viewProjectionMatrix, float x, float y, float z);
	void drawRotatedBox(glm::mat4 viewProjectionMatrix, float x, float y, float z, float angle, glm::vec3 center, glm::vec3 axis, glm::vec3 color);
	void drawFloorTile(glm::mat4 viewProjectionMatrix, float x, float z);
	void drawFloorTileFrame(glm::mat4 viewProjectionMatrix, float x, float z);
	void drawVictoryTile(glm::mat4 viewProjectionMatrix, float x, float z);
private:
    GLuint _vertexArrayObject;
    glm::mat4 model;
    Shaders* _shader;
};

#endif