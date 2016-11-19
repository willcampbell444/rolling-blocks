#ifndef PAUSE_H
#define PAUSE_H

#include <string>
#include <vector>
#include <renderer.h>
#include <glm/glm.hpp>
#include <globals.h>

struct Option {
	std::string text;
	unsigned int type;
	int value = 1;
	bool hover = false;
	Option(std::string text, unsigned int type): text(text), type(type) {}
};

class Pause {
public:
	void setPlay();
	void setMenu();
	void update(glm::vec2 mousePos, float height);
	void resize(int w, int h);
	void setRenderer(Renderer* renderer);
	void draw(float height);
	void click(bool mouseClick);
	int  clicked();
private:
	std::vector<Option> _options;
	int _width = 800;
	int _height = 600;
	int _clicked = -1;
	Renderer* _renderer;
};

#endif