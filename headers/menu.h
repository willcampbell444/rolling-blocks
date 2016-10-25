#ifndef MENU_H
#define MENU_H

#include <GL/glew.h>
#include <shaders.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <shaders.h>
#include <globals.h>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <iostream>

class Menu {
public:
	Menu(Shaders* shader);
	void setOptions(std::vector<const char*> options, int dir);
	void draw(glm::mat4 viewProjectionMatrix);
	glm::vec3 getCameraPos();
	glm::vec2 getCameraDistance();
	void update();
	bool isStill();
	void end();
	void select();
	int result();
	void move(int direction);
private:
	unsigned int loadLetter(bool bits[25]);
	void setCamera();
	std::unordered_map<char, unsigned int> _chars;

	int _currentPeice = 0;
	std::vector<std::vector<unsigned int>> _options;

	bool _isBeginning = false;
	bool _isCameraTransition = false;
	bool _isTransition = false;
	bool _isEndTransition = false;
	bool _wait = false;
	bool _done = false;
	bool _forcedEnd = false;
	int _frame = 0;

	float _angle = 90.0f;
	float _height = 0;

	GLuint _blockVAO;
	GLuint _lineVAO;

	Shaders* _shader;

	glm::vec3 _cameraPos;
	glm::vec2 _cameraDistance;
	glm::vec3 _oldCameraPos;
	glm::vec2 _oldCameraDistance;
	glm::vec3 _newCameraPos;
	glm::vec2 _newCameraDistance;
};

#endif