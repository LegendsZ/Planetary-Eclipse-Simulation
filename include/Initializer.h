#ifndef INITIALIZER_H
#define INITIALIZER_H

#include <string>
#include <fstream>

#include "Window.h"
#include "Misc.h"
#include "callbackFunctions.h"
#include "Game.h"
#include "OpenGLLoader.h"

namespace Initializer{
    inline std::string errorMessage;
    // Initialize GLUT
    //bool initGlut(int argc, char** argv, const int& vWidth, const int& vHeight);

    // Read a file and return its contents
    std::string readFile(const std::string& filePath);

    // Print OpenGL information
    void printGLInfo();

    // Set up and enable lighting
    bool initOpenGL(Window* window);

    // Set up callback functions for glut
    bool setCallbackFunctions(GLFWwindow* window);

    // Initializes all
    bool InitializeAll(int width, int height, int fps, int vsync);

    //Initializes game objects
    bool initializeGameObjects();
}

#endif //INITIALIZER_H
