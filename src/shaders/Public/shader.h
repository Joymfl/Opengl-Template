//
// Created by joydm on 29-06-2024.
//
#include <stdbool.h>
#include "glad/glad.h"

#ifndef INC_3DTESTER_SHADER_H
#define INC_3DTESTER_SHADER_H


struct ShaderInfo {
    char *filename;
    GLenum type;
    GLuint shader;
};

GLuint init_shaders(struct ShaderInfo *shaders);

void activateShader(int ID);

void setBool(char *name, bool value, unsigned int ID);

void setInt(const char *name, int value, unsigned int ID);

void setFloat(const char *name, float value, unsigned int ID);

#endif //INC_3DTESTER_SHADER_H
