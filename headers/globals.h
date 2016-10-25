#ifndef GLOBALS_H
#define GLOBALS_H

#include <glm/glm.hpp>

namespace GLOBAL {
	const glm::vec3 BACKGROUND(0.168627, 0.188235, 0.23137);
	const glm::vec3 FLOOR_COLOR(0.752941, 0.772549, 0.8078431);
	const glm::vec3 FLOOR_BOTTOM(0.168627, 0.188235, 0.23137);
	const glm::vec3 FLOOR_BORDER(1, 1, 1);
	const glm::vec3 PLAYER_COLOR(0.752941, 0.772549, 0.8078431);
	const glm::vec3 DONE_PLAYER_COLOR(1, 0.772549, 0.8078431);
	const glm::vec3 PLAYER_BORDER(0, 0, 0);
	const glm::vec3 STATIC_BORDER(1, 1, 1);
	const glm::vec3 VICTORY_COLOR(1, 0.772549, 0.8078431);
	const glm::vec3 VICTORY_BORDER(1, 1, 1);

	const float GAP = 0.05f;
	const float BLOCK_WIDTH = 1.0f-(GAP*2.0f);
	const float BOTTOM = -2.0f;

	const float FALL_HEIGHT = 7;

	const float FRAMES = 50.0f;

	const int STATE_PLAY = 0;
	const int STATE_MENU = 1;
	const int STATE_PAUSE = 2;
}

#endif