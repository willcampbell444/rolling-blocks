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
	Option(std::string text, unsigned int type): text(text), type(type) {}
	Option(std::string text, unsigned int type, int value): text(text), type(type), value(value) {}
};

class Pause {
public:
	void setPlay(bool showControls);
	void setMenu(bool showControls);
	void mouseMove(glm::vec2 mousePos, float height);
	void keyPress(int dir);
	void resize(int w, int h);
	void setRenderer(Renderer* renderer);
	void draw(float height);
	void click(bool click);
	void setCurrent(int x);
	int  clicked();
private:
	std::vector<Option> _options;
	int _width = 800;
	int _height = 600;
	int _clicked = -1;
	int _current = -1;
	Renderer* _renderer;
};

#endif