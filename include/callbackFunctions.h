#ifndef CALLBACKFUNCTIONS_H
#define CALLBACKFUNCTIONS_H

#include <iostream>
#include <OpenGLLoader.h>
#include "Window.h"
#include "Logger.h"

namespace callbackFunctions {
    void reshape(GLFWwindow* window, int width, int height);
    void mouse(GLFWwindow* window, int button, int action, int mods);
    void mouseMotionHandler(GLFWwindow* window, double xpos, double ypos);
    void keyHandler(GLFWwindow* window, int key, int scancode, int action, int mods);
    void errorHandler(int error, const char* description);
    void windowCloseHandler(GLFWwindow* window);
    void signalWindowCloseHandler(int sigNum);
}

#endif //CALLBACKFUNCTIONS_H
