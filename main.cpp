// main.cpp
#include "Game.h"

int main() {
    Game game;
    if (game.init()) {
        game.run();
    }
    game.cleanup();
    return 0;
}
