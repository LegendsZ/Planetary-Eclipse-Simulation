#include "../include/Logger.h"

#ifdef DEBUG

namespace logger {
    void l_log(int type, const std::string& message) {
        std::string sType = "";
        switch (type) {
            case 0:
                sType = "INFO";
            break;
            case 1:
                sType = "WARNING";
            break;
            case 2:
                sType = "ERROR";
            break;
            default:
                sType = "UNKNOWN";
            break;
        }
        (type != 2 ? std::cout : std::cerr) << sType << ": " << message << "\n";
    }

    void l_checkError() {
        GLenum err;
        while ((err = glGetError()) != GL_NO_ERROR) {
            std::cerr << err; // Change to log!
        }
    }
}

#endif