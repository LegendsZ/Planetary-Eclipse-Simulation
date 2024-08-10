#ifndef INITIALIZER_H
#define INITIALIZER_H

#include <string>

#include "Window.h"
#include "Misc.h"
#include "callbackFunctions.h"
#include "Game.h"

namespace Initializer{
    inline std::string errorMessage;
    // Initialize GLUT
    //bool initGlut(int argc, char** argv, const int& vWidth, const int& vHeight);

    // Set up and enable lighting
    bool initOpenGL();

    // Set up callback functions for glut
    bool setCallbackFunctions(GLFWwindow* window);

    // Initializes all
    bool InitializeAll(int width, int height, int fps, int vsync);

    //Initializes game objects
    bool initializeGameObjects();
}

#endif //INITIALIZER_H
