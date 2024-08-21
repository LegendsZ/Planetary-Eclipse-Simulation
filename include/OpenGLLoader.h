#ifndef OPENGLLOADER_H
#define OPENGLLOADER_H

#include "Vertex.h"
#include "glad/glad.h"
#include "Logger.h"
#include <GLFW/glfw3.h>

static drawDetails uploadMesh_deprecated(const std::vector<vertex>& vertices, const std::vector<uint32_t> elements){
    if (vertices.empty() || elements.empty()) throw("Empty vectors!");

    uint32_t VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    l_checkError();
    //creation and setting vbo
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, sizeof(vertex), (const void*)offsetof(vertex,_pos));
    glEnableVertexAttribArray(0);
    l_checkError();
    //creation and setting ebo
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(uint32_t), elements.data(), GL_STATIC_DRAW);
    l_checkError();
    glBindVertexArray(0);
    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1,&EBO);
    l_checkError();
    l_log(0, "Loaded mesh!");
    return drawDetails(VAO, elements.size());
}

static drawDetails uploadMesh(const GLfloat* vertices, const GLfloat* colours, const int vCount, const GLuint* elems, const int eCount){
    GLuint vaoHandle;
    glGenVertexArrays(1, &vaoHandle);
    glBindVertexArray(vaoHandle);
    l_checkError();
    GLuint vboHandles[2];
    glGenBuffers(2, vboHandles);//one for vertices, one for colours
    l_checkError();
    GLuint verticesBufferHandle = vboHandles[0];
    glBindBuffer(GL_ARRAY_BUFFER, verticesBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, vCount * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);
    l_checkError();
    GLuint colourBufferHandle = vboHandles[1];
    glBindBuffer(GL_ARRAY_BUFFER, colourBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, vCount * sizeof(GLfloat), colours, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);
    l_checkError();
    GLuint eboHandle;
    glGenBuffers(1, &eboHandle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboHandle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, eCount * sizeof(GLuint), elems, GL_STATIC_DRAW);
    l_checkError();
    glBindVertexArray(0);
    glDeleteBuffers(2,vboHandles);
    glDeleteBuffers(1,&eboHandle);
    l_checkError();
    l_log(0, "Loaded mesh!");
    return {vaoHandle, (uint32_t) eCount};
}

static void unloadMesh(std::vector<drawDetails>& details) {
    for (auto& d : details) {
        glDeleteBuffers(1, &d.vao);
    }
    details.clear();
    l_log(0, "Unloaded meshes!");
}

static GLuint loadShader(const char* vertex, const char* fragment) {
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertex, nullptr);
    glCompileShader(vertexShader);
    GLint success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        l_log(2, "Vertex shader compilation failed: " + std::string(infoLog));
        return -1;
    }
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragment, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        l_log(2, "Fragment shader compilation failed: " + std::string(infoLog));
        return -1;
    }

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        l_log(2, "Shader program linking failed: " + std::string(infoLog));
        return -1;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return shaderProgram;
}

#endif //OPENGLLOADER_H
