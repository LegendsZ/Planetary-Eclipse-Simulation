#include "../include/Game.h"

namespace game{
    bool startGame(){
        game::running = true;
        game::bkgdThread = std::thread(backgroundLogic);
        return true;
    }
    bool stopGame(){
        running = false;
        bkgdThread.join();
        return true;
    }
    void backgroundLogic(){
        while(running){
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }
}