#include "graphics.h"

#include <iostream>

Graphics::Graphics() : shader("shaders/vertex.glsl", "shaders/fragment.glsl") {}

bool Graphics::init() {
    if (!shader.load())
    {
        std::cerr << "Falha ao carregar os shaders!" << std::endl;

        return false;
    }

    setupGraphics();
    return true;
}

void Graphics::setupGraphics() {
    GLfloat vertices[] = {
        // X     Y      Z
        -0.5f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f,
        0.0f,  0.5f, 0.0f,
        0.0f, -0.5f, 0.0f
    };

    GLuint indices[] = {
        0, 1, 2,
        0, 1, 3
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void Graphics::render(Window& window) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    float time = glfwGetTime();
    int timerLoc = glGetUniformLocation(shader.getProgram(), "time");

    if (window.getKey(GLFW_KEY_SPACE, GLFW_PRESS))  {
        paused = true;
    } else if (window.getKey(GLFW_KEY_SPACE, GLFW_RELEASE)){
        paused = false;
    }

    if (window.getKey(GLFW_KEY_R, GLFW_PRESS)) {
        glfwSetTime(0.0f);
    }
    
    if (!paused) {
        glUniform1f(timerLoc, time);
    } else {
        glUniform1f(timerLoc, 0);
    }

    glUseProgram(shader.getProgram());
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Graphics::quit() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shader.getProgram());
}