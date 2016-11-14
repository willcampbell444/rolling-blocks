#include <game.h>

int main()
{
    Game game;
    while(!game.end()) {
        game.update();
        game.draw();
    }
}