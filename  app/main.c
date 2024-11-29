#include <stdio.h>
#include "math.h"
#include"glad/glad.h"
#include "GLFW/glfw3.h"
#include "shader.h"
#include "openglHelper.h"

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

GLuint shader_program;

// Callback function to resize opengl viewport
void framebuffer_size_callback(GLFWwindow *glfWwindow, int width, int height);

// input processing
void processInput(GLFWwindow *window);

void RenderLoop(GLFWwindow *window);

void Cleanup(GLFWwindow *window);

int main() {
    GLFWwindow *window = setupContext();
    if (!window) {
        perror("Failed to set up GLFW window context. Quitting ......");
        return -1;
    }
    struct ShaderInfo shaders[3] = {
            {
                    .shader = 0,
                    .type = GL_VERTEX_SHADER,
                    .filename = "vertex"
            },
            {
                    .shader = 0,
                    .type = GL_FRAGMENT_SHADER,
                    .filename = "fragment"
            },
            {
                    .type = GL_NONE,
            }
    };

    shader_program = init_shaders((struct ShaderInfo *) &shaders);
    GLuint vao;
    glCreateVertexArrays(1, &vao);
    glBindVertexArray(vao);


    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glPointSize(40.);
    RenderLoop(window);

    Cleanup(window);
    return 0;
}

void RenderLoop(GLFWwindow *window) {
    while (!glfwWindowShouldClose(window)) {
        processInput(window);


        // Rendering commands
        float CurrentTime = (float) glfwGetTime();
        const GLfloat color[4] = {sinf(CurrentTime), 0.3f, 0.4f, 1.0f};
        glClearBufferfv(GL_COLOR, 0, color);

        glUseProgram(shader_program);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Cleanup(GLFWwindow *window) {
    glfwTerminate();
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, 1);
    }
}
