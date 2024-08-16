#ifndef LOGGER_H
#define LOGGER_H

#ifdef DEBUG

#include <iostream>
#include "glad/glad.h"
#include <string>

namespace logger {
    enum l_type{
        INFO,
        WARNING,
        ERROR
    };

    void l_log(int type, const std::string& message);
    void l_checkError();
}

#define l_log(type, message) logger::l_log(type, message)
#define l_checkError() logger::l_checkError()

#else

#define l_log(type, message)
#define l_checkError()

#endif //DEBUG

#endif //LOGGER_H
