#include <levelEdit.h>
#include <string>
#include <iostream>

int main(int argc, char *argv[]) {
	if (argc > 1) {
		std::string fileName = std::string("maps/") + std::string(argv[1]) + std::string(".map");
		LevelEdit levelEdit(fileName);
		while (!glfwWindowShouldClose(levelEdit.getWindow()) && !levelEdit.end()) {
			levelEdit.update();
			levelEdit.draw();
		}
	} else {
		std::cout << "You must give a map name" << std::endl;
	}
}