#include "shader.h"
#include "stdio.h"
#include "stdlib.h"

char *readFileToString(const char *fileName);

GLuint init_shaders(struct ShaderInfo *shaders) {
    if (shaders == NULL)
        return 0;

    GLuint program = glCreateProgram();
    struct ShaderInfo *entry = shaders;

    while (entry->type != GL_NONE) {
        GLuint shader = glCreateShader(entry->type);
        entry->shader = shader;

        const GLchar *source = readFileToString(entry->filename);
        // On error delete all shaders in object
        if (source == NULL) {
            for (entry = shaders; entry->type != GL_NONE; ++entry) {
                glDeleteShader(entry->shader);
                entry->shader = 0;
            }
            return 0;
        }
        glShaderSource(shader, 1, &source, NULL);
        free((void *) source);
        glCompileShader(shader);

        GLint compiled;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled) {

            GLsizei len;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
            GLchar *log = (GLchar *) malloc(len + 1);
            glGetShaderInfoLog(shader, len, &len, log);
            printf("Shader compilation failed: %s\n", log);
            return 0;
        }
        glAttachShader(program, shader);
        ++entry;
    }
    glLinkProgram(program);

    GLint linked;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (!linked) {
        GLsizei len;
        glGetProgramiv(program, GL_LINK_STATUS, &len);

        GLchar *log = (GLchar *) malloc(len + 1);
        glGetProgramInfoLog(program, len, &len, log);
        printf("Shader linking failed: %s\n", log);
        for (entry = shaders; entry->type != GL_NONE; ++entry) {
            glDeleteShader(entry->shader);
            entry->shader = 0;
        }
        return 0;
    }

    return program;
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
    size_t size = snprintf(NULL, 0, "../../shaders/%s.glsl", fileName) + 1; // add 1 for null char
    // allocate mem for buffer
    char *pathBuf = (char *) malloc(size);
    if (pathBuf == NULL)
        printf("Failed to allocate mem for dynamic filepath");

    sprintf(pathBuf, "../../shaders/%s.glsl", fileName);
    printf("file path: %s\n", pathBuf);
    FILE *file;
    char *buffer;
    long file_size;

    // open the file for reading
    file = fopen(pathBuf, "r");
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
