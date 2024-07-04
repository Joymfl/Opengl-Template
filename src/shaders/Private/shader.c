#include "shader.h"
#include "stdio.h"
#include "stdlib.h"

char *readFileToString(const char *fileName);

int init_shaders(const char *vertexPath, const char *fragmentPath) {
    const char *vertexCode;
    const char *fragmentCode;
    vertexCode = readFileToString(vertexPath);
    fragmentCode = readFileToString(fragmentPath);

    //compiling
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexCode, NULL);
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION::FAILED\n%s\n", infoLog);
    }
    printf("vertex shader compiled succesfully\n");

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentCode, NULL);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION::FAILED\n%s\n", infoLog);
    }

    printf("fragment shader compiled succesfully\n");

    // program
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertex);
    glAttachShader(shaderProgram, fragment);
    glLinkProgram(shaderProgram);
    glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("ERROR::SHADER::PROGRAM::LINKING::FAILED\n%s\n", infoLog);
    }
    // cleanup  
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    free((void *) vertexCode);
    free((void *) fragmentCode);
    return shaderProgram;
}

void setBool(char *name, bool value, unsigned int ID) {
    glUniform1i(glGetUniformLocation(ID, name), (int) value);

}

void setInt(const char *name, int value, unsigned int ID) {
    glUniform1i(glGetUniformLocation(ID, name), value);
}

void setFloat(const char *name, float value, unsigned int ID) {
    glUniform1f(glGetUniformLocation(ID, name), value);
}


char *readFileToString(const char *fileName) {
    FILE *file;
    char *buffer;
    long file_size;

    // open the file for reading
    file = fopen(fileName, "r");
    if (file == NULL) {
        perror("Couldn't read file");
        return NULL;
    }

    // size of file
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // set memory to hold file content
    buffer = (char *) malloc((file_size + 1) * sizeof(char));
    if (buffer == NULL) {
        perror("Mem alloc failed");
        fclose(file);
        free(buffer);
        return NULL;
    }
    size_t bytes = fread(buffer, 1, file_size, file);
    buffer[bytes] = '\0';

    fclose(file);
    return buffer;
}