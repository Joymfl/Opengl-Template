#include <stdio.h>
#include "math.h"
#include"glad/glad.h"
#include "GLFW/glfw3.h"
#include "shader.h"
#include "openglHelper.h"


// Callback function to resize opengl viewport
void framebuffer_size_callback(GLFWwindow *glfWwindow, int width, int height);

// input processing
void processInput(GLFWwindow *window);

int main() {
    GLFWwindow *window = setupContext();
    if (!window) {
        perror("Failed to set up GLFW window context. Quitting ......");
        return -1;
    }

    // initialize shaders
    int shaderProgram = init_shaders("../../shaders/vertex_shader.glsl", "../../shaders/fragment_shader.glsl");
    // Define and compile shader object

    // Defining vertices and bind VBO object to gpu memory
    float vertices[] = {
            // Positions                      // colors
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom left
            .5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right
            0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f // top
    };

    // Setup and Assign a VAO and VBO
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);



    // setup opengl viewport
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Code for wireframe
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // render loop
    while (!glfwWindowShouldClose(window)) {
        processInput(window);


        // Rendering commands
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // render triangle
//        float timeValue = glfwGetTime();
//        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        int offsetLocation = glGetUniformLocation(shaderProgram, "offset");
        glUseProgram(shaderProgram);
        glUniform1f(offsetLocation, 0.5f);

        //draw first triangle
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, 1);
    }
}