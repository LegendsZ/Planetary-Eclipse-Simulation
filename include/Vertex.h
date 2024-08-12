#ifndef VERTEX_H
#define VERTEX_H

#include "VECTOR3D.h"

struct vertex {
    vertex (float x, float y, float z): _pos{x, y, z} {}
    VECTOR3D _pos = {0.0f, 0.0f, 0.0f};
};

struct drawDetails{
    drawDetails(uint32_t vao, uint32_t numElements): vao(vao), numElements(numElements) {}
    uint32_t vao=0;
    uint32_t numElements=0;
};

#endif //VERTEX_H
