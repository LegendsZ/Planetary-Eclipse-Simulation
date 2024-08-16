#include "../include/callbackFunctions.h"

#include <Game.h>

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
            l_log(0,"Key pressed: " + std::to_string(key));
        }else if (action == GLFW_RELEASE){
            // Your keyboard repeat handling code here
            l_log(0,"Key released: " + std::to_string(key));
        }
    }

    void errorHandler(int error, const char* description) {
        std::cerr << "GLFW Error: " << description << "\n";
        l_log(2,description);
    }

    void windowCloseHandler(GLFWwindow* window) {
        l_log(0,"Closing window!");
        Window* found = Window::findWindow(window);
        if (!found) {
            std::cerr << "Unexpected error: GLFWwindow* not found!\n";
            l_log(3, "Unexpected error: GLFWwindow* not found!");
            return;
        }
        found->stopRenderLoop();
        found->close();
        unloadMesh(found->_drawDetails);
    }

    void signalWindowCloseHandler(int sigNum) {
        l_log(0, "Closing all windows!");
        for (Window* window : Window::windows) {
            windowCloseHandler(window->_glfwWindow);
        }
        game::stopGame();
    }


}
