#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <game.h>

int main()
{
    Game game;
    while(!glfwWindowShouldClose(game.getWindow())) {
        game.update();
        game.draw();
    }
}