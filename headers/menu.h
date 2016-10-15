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
	void setOptions(std::string* options, int numOptions);
	void draw(glm::mat4 viewProjectionMatrix);
	glm::vec3 getCameraPos() {return glm::vec3(-10, 3, 20);};
	glm::vec2 getCameraDistance() {return glm::vec2(1, 1);};
	void update();
private:
	unsigned int loadLetter(bool bits[25]);
	std::unordered_map<char, unsigned int> _chars;

	int _currentPeice = 0;
	std::vector<std::vector<unsigned int>> _options;

	GLuint _floorVAO;
	GLuint _selectedVAO;
	GLuint _unselectedVAO;
	GLuint _floorLineVAO;
	GLuint _selectedLineVAO;
	GLuint _unselectedLineVAO;

	Shaders* _shader;
};

#endif