#ifndef CALLBACKFUNCTIONS_H
#define CALLBACKFUNCTIONS_H

#include <GLFW/glfw3.h>

namespace callbackFunctions {
    void reshape(GLFWwindow* window, int width, int height);
    void mouse(GLFWwindow* window, int button, int action, int mods);
    void mouseMotionHandler(GLFWwindow* window, double xpos, double ypos);
    void keyHandler(GLFWwindow* window, int key, int scancode, int action, int mods);
}

#endif //CALLBACKFUNCTIONS_H
