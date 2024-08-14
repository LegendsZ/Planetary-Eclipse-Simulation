#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include "glad/glad.h"
#include <string>

namespace logger {
    enum l_type{
        INFO,
        WARNING,
        ERROR
    };

    inline void l_log(int type, const std::string& message) {
        std::string sType = "";
        switch (type){
            case 0:
                sType="INFO";
                break;
            case 1:
                sType="WARNING";
                break;
            case 3:
                sType="ERROR";
                break;
            default:
                sType="UNKNOWN";
                break;
        }
        (type != 3 ? std::cout : std::cerr) << sType << ": " << message << "\n";
    }

    inline void l_checkError(){
        GLenum err;
        while((err = glGetError()) != GL_NO_ERROR){
            std::cerr << err; //CHANGE TO LOG!
        }
    }
}

#endif //LOGGER_H
