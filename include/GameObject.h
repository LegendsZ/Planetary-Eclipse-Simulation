#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "glad/glad.h"
#include "VECTOR3D.h"

struct GameObject{
private:
public:
    VECTOR3D _pos;
    bool _physics = false;

    GameObject(VECTOR3D pos, bool physics): _pos(pos), _physics(physics) {}
};

#endif //GAMEOBJECT_H
