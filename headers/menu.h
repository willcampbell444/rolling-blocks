#ifndef MENU_H
#define MENU_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <globals.h>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <iostream>
#include <renderer.h>
#include <ft2build.h>
#include FT_FREETYPE_H  

struct MenuOption {
	bool completed;
	int moves;
	const char* fileName;
	MenuOption(const char* fileName, bool completed, int moves): fileName(fileName), completed(completed), moves(moves) {};
};

class Menu {
public:
	Menu(Renderer* renderer);
	void setOptions(std::vector<MenuOption> options, int dir, int optionNum);
	void draw(glm::mat4 viewProjectionMatrix);
	glm::vec3 getCameraPos();
	glm::vec2 getCameraDistance();
	void update(GLfloat deltaTime);
	bool isStill();
	void end();
	void select();
	int result();
	void move(int direction);
private:
	unsigned int loadLetter(bool bits[25]);
	void setCamera();
	void fillFloor();
	std::unordered_map<char, unsigned int> _chars;

	int _currentPeice = 0;
	std::vector<std::vector<unsigned int>> _options;
	std::vector<MenuOption> _menuOptions;

	std::vector<glm::vec2> _floorPeices;
	std::vector<glm::vec2> _victoryFloorPeices;

	bool _isBeginning = false;
	bool _isCameraTransition = false;
	bool _isTransition = false;
	bool _isEndTransition = false;
	bool _wait = false;
	bool _done = false;
	bool _forcedEnd = false;

	float _timeSinceTransition = 0;

	float _angle = 90.0f;
	float _height = 0;

	Renderer* _renderer;

	glm::vec3 _cameraPos;
	glm::vec2 _cameraDistance;
	glm::vec3 _oldCameraPos;
	glm::vec2 _oldCameraDistance;
	glm::vec3 _newCameraPos;
	glm::vec2 _newCameraDistance;
};

#endif