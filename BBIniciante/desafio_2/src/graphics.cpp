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
    vertices[0] = -0.5f;
    vertices[1] = 0.0f;
    vertices[2] = 0.0f;

    vertices[3] = 0.5f;
    vertices[4] = 0.0f;
    vertices[5] = 0.0f;

    vertices[6] = 0.0f;
    vertices[7] = (waterLevel * 2.0f) - 1.0f;
    vertices[8] = 0.0f;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Graphics::updateVertices() {
    float yPos = (waterLevel * 2.0f) - 1.0f;
    vertices[7] = yPos;

    changeColor(yPos);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Graphics::changeColor(float yPos) {
    int colorLoc = glGetUniformLocation(shader.getProgram(), "ourColor");
    if (yPos >= -1.0f and yPos <= -0.4f) {
        glUniform4f(colorLoc, 0.0f, 0.8f, 1.0f, 1.0f);
    } else if (yPos > -0.4f and yPos <= 0.4f) {
        glUniform4f(colorLoc, 0.0f, 0.0f, 1.0f, 1.0f);
    } else if (yPos > 0.4f and yPos <= 1.0f) {
        glUniform4f(colorLoc, 0.0f, 0.0f, 0.5f, 1.0f);
    }
}

void Graphics::render(Window& window) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if (!pressed) {
        if (window.getKey(GLFW_KEY_UP, GLFW_PRESS) and !(vertices[7] > 1.0)) {
            waterLevel += 0.0001f;
        } else if (window.getKey(GLFW_KEY_DOWN, GLFW_PRESS) and !(vertices[7] < -1.0)) {
            waterLevel -= 0.0001f;
        }

        waterLevelChanged = true;
        pressed = true;
    } else {
        if (window.getKey(GLFW_KEY_UP, GLFW_RELEASE) || window.getKey(GLFW_KEY_DOWN, GLFW_RELEASE)) {
            pressed = false;
        }
    }
    

    if (waterLevelChanged) {
        updateVertices();
    }

    glUseProgram(shader.getProgram());
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Graphics::quit() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shader.getProgram());
}