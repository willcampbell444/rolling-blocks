#ifndef LEVELEDIT_H
#define LEVELEDIT_H

#include <shaders.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map.h>
#include <globals.h>
#include <fstream>
#include <vector>
#include <cmath>
#include <renderer.h>

class LevelEdit {
public:
	LevelEdit(std::string fileName);
	bool end();
	GLFWwindow* getWindow();
	void draw();
	void update();
	void setTile(int x, int z, int type);
private:
    GLFWwindow* _window;

    Renderer* _renderer;

    glm::mat4 _viewMatrix;
    glm::mat4 _projectionMatrix;
    glm::mat4 _projectionViewMatrix;

    glm::vec3 _cameraPos;

    float _viewAngle = 0;

    int _width, _length;

    bool _mouseOn = true;
    glm::vec3 _selected;

    std::string _fileName;

    std::vector<std::vector<int>> _tiles;
    std::vector<glm::vec3> _player;
};

#endif