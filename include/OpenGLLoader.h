#ifndef OPENGLLOADER_H
#define OPENGLLOADER_H

#include "Vertex.h"
#include "glad/glad.h"
#include "Logger.h"
#include <GLFW/glfw3.h>

static drawDetails uploadMesh(const std::vector<vertex>& vertices, const std::vector<uint32_t> elements){
    if (vertices.empty() || elements.empty()) throw("Empty vectors!");

    uint32_t VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    logger::l_checkError();
    //creation and setting vbo
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, sizeof(vertex), (const void*)offsetof(vertex,_pos));
    glEnableVertexAttribArray(0);
    logger::l_checkError();
    //creation and setting ebo
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(uint32_t), elements.data(), GL_STATIC_DRAW);
    logger::l_checkError();
    glBindVertexArray(0);
    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1,&EBO);
    logger::l_checkError();
    logger::l_log(0, "Loaded mesh!");
    return drawDetails(VAO, elements.size());
}

static void unloadMesh(std::vector<drawDetails>& details) {
    for (auto& d : details) {
        glDeleteBuffers(1, &d.vao);
    }
    details.clear();
    logger::l_log(0, "Unloaded mesh!");
}

#endif //OPENGLLOADER_H
