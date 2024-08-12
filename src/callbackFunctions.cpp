#include "../include/callbackFunctions.h"

namespace callbackFunctions{

    void reshape(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    }

    void mouse(GLFWwindow* window, int button, int action, int mods) {
        // Your mouse handling code here
    }

    void mouseMotionHandler(GLFWwindow* window, double xpos, double ypos) {
        // Your mouse motion handling code here
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) //support drag
        {
            return;
        }
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

    void errorHandler(int error, const char* description) {
        std::cerr << "GLFW Error: " << description << "\n";
    }

    void windowCloseHandler(GLFWwindow* window) {
        Window* found = Window::findWindow(window);
        if (!found) {
            std::cerr << "Unexpected error: GLFWwindow* not found!\n";
            return;
        }
        unloadMesh(found->_drawDetails);
    }

}
