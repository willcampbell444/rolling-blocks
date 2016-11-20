#include <game.h>

int main(int argc, char* argv[])
{
    Game game;
    while(!game.end()) {
        game.update();
        game.draw();
    }
}