#ifndef GAME_H
#define GAME_H

#include <vector>
#include <thread>

class GameObject; //forward declare

namespace game {
    inline std::vector<GameObject*> gameObjects;
    inline std::thread bkgdThread;
    inline bool running = false;
    void backgroundLogic();
    bool startGame();
    bool stopGame();
}

#endif //GAME_H
