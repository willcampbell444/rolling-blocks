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
	Option(std::string text, unsigned int type): text(text), type(type) {}
};

class Pause {
public:
	void setPlay();
	void setMenu();
	void update(glm::vec2 mousePos);
	void resize(int w, int h);
	void setRenderer(Renderer* renderer);
	void draw(float height);
private:
	std::vector<Option> _options;
	int _width = 800;
	int _height = 600;
	Renderer* _renderer;
};

#endif