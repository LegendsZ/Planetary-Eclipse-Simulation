#include "../include/callbackFunctions.h"

#include <iostream>

namespace callbackFunctions{

    void reshape(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    }

    void mouse(GLFWwindow* window, int button, int action, int mods) {
        // Your mouse handling code here
    }

    void mouseMotionHandler(GLFWwindow* window, double xpos, double ypos) {
        // Your mouse motion handling code here
    }

    void keyHandler (GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (action == GLFW_PRESS) {
            // Your keyboard down handling code here
            std::cout << "Key pressed: " << key << "\n";
        }else if (action == GLFW_RELEASE){
            // Your keyboard repeat handling code here
            std::cout << "Key released: " << key << "\n";
        }
    }

}