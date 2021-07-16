#include "Game.hpp"

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance,LPSTR lpszArgument, int nCmdShow){
    srand(time(NULL));
    Game game;
    game.run();
    return 0;
}