#ifndef QUERYATTRIBUTES_H
#define QUERYATTRIBUTES_H

#include "glad/glad.h"
#include "Logger.h"

static void queryAttributes(GLuint program){
    //glBindVertexArray(vao);

    GLint numAttribs;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &numAttribs);
    l_log(0, "Maximum number of vertex attributes supported: " + std::to_string(numAttribs));

    GLint activeAttribs;
    glGetProgramiv(program, GL_ACTIVE_ATTRIBUTES, &activeAttribs);
    l_log(0, "Number of active attributes: " + std::to_string(activeAttribs));

    for (GLint i = 0; i < activeAttribs; ++i) {
        char name[256];
        GLsizei length;
        GLint size;
        GLenum type;
        glGetActiveAttrib(program, i, sizeof(name), &length, &size, &type, name);

        GLint location = glGetAttribLocation(program, name);
        l_log(0, "Attribute #" + std::to_string(i) + ":");
        l_log(0, "  Name: " + std::string(name));
        l_log(0, "  Type: " + std::to_string(type));
        l_log(0, "  Size: " + std::to_string(size));
        l_log(0, "  Location: " + std::to_string(location));
    }

    //glBindVertexArray(0);
}

static void queryMax() {
    GLint numAttribs;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &numAttribs);
    l_log(0, "Maximum number of vertex attributes supported: " + std::to_string(numAttribs));

    GLint numUniforms;
    glGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS, &numUniforms);
    l_log(0, "Maximum number of vertex uniform components supported: " + std::to_string(numUniforms));

    GLint numVaryings;
    glGetIntegerv(GL_MAX_VARYING_FLOATS, &numVaryings);
    l_log(0, "Maximum number of varying floats supported: " + std::to_string(numVaryings));

    GLint numTextures;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &numTextures);
    l_log(0, "Maximum number of texture image units supported: " + std::to_string(numTextures));

    GLint numVertexTextures;
    glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &numVertexTextures);
    l_log(0, "Maximum number of vertex texture image units supported: " + std::to_string(numVertexTextures));

    GLint numCombinedTextures;
    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &numCombinedTextures);
    l_log(0, "Maximum number of combined texture image units supported: " + std::to_string(numCombinedTextures));

    GLint numUniformBlocks;
    glGetIntegerv(GL_MAX_VERTEX_UNIFORM_BLOCKS, &numUniformBlocks);
    l_log(0, "Maximum number of vertex uniform blocks supported: " + std::to_string(numUniformBlocks));

    GLint numUniformBlockComponents;
    glGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS, &numUniformBlockComponents);
    l_log(0, "Maximum number of vertex uniform components supported: " + std::to_string(numUniformBlockComponents));

    GLint numUniformBlockBindings;
    glGetIntegerv(GL_MAX_VERTEX_UNIFORM_BLOCKS, &numUniformBlockBindings);
    l_log(0, "Maximum number of vertex uniform block bindings supported: " + std::to_string(numUniformBlockBindings));

    /*GLint numShaderStorageBlocks;
    glGetIntegerv(GL_MAX_VERTEX_SHADER_STORAGE_BLOCKS, &numShaderStorageBlocks);
    l_log(0, "Maximum number of vertex shader storage blocks supported: " + std::to_string(numShaderStorageBlocks));*/
}

#endif //QUERYATTRIBUTES_H
