#ifndef OPENGLDRAW_H
#define OPENGLDRAW_H

#include "OpenGLLoader.h"

static void draw(const std::vector<drawDetails>& details) {
    for (const auto& d : details) {
        glBindVertexArray(d.vao);
        glDrawElements(GL_TRIANGLES, d.numElements, GL_UNSIGNED_INT, nullptr);
    }
    glBindVertexArray(0);
}

#endif //OPENGLDRAW_H