#ifndef GAME_H
#define GAME_H

#include <vector>
#include <thread>
#include "GameObject.h"

namespace game {
    inline std::vector<GameObject*> gameObjects;
    inline std::thread bkgdThread;
    inline bool running = false;

    //Will load/create game objects; should be executed first
    bool initializeGame();

    //main logic loop; should run physics
    void backgroundLogic();

    //will start game logic loop
    bool startGame();

    //will end game logic loop
    bool stopGame();
}

#endif //GAME_H
