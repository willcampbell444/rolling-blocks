#include <game.h>

int main()
{
    Game game;
    while(!glfwWindowShouldClose(game.getWindow()) && !game.end()) {
        game.update();
        game.draw();
    }
}