#include "graphics.h"

#include <iostream>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
    float vertices[] = {
        // X     Y      Z
         0.0f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
    };

    unsigned int indices[] = {
        0, 1, 2
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

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Graphics::updateCPUCharge() {
    if (updatedCharge) {
        float pulse = (sin(glfwGetTime() * 2.0f) + 1.0f) * 0.5f;

        scale = 0.8f + pulse * (1.0f - 0.8f);

        updatedCharge = false;
    }
}

void Graphics::updateColor() {
    glm::vec3 green(0.0f, 1.0f, 0.0f);
    glm::vec3 yellow(1.0f, 1.0f, 0.0f);
    glm::vec3 red(1.0f, 0.0f, 0.0f);

    float factor = cpuCharge / 100.0f;

    if (cpuCharge <= 30.0f) {
        interpolatedColor = glm::mix(green, yellow, factor / 30.0f);
    } else if (cpuCharge <= 70.0f) {
        interpolatedColor = glm::mix(yellow, red, (factor - 30.0f) / 40.0f);
    } else {
        interpolatedColor = red;
    }
}

void Graphics::render(Window& window) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    updateCPUCharge();
    updateColor();

    int colorLoc = glGetUniformLocation(shader.getProgram(), "ourColor");
    glUniform3fv(colorLoc, 1, &interpolatedColor[0]);

    Input input = window.getInput();
    if (input.isKeyPressed(GLFW_KEY_UP)) {
        cpuCharge += 0.1f;

        if (cpuCharge > 100.0f) { cpuCharge = 100.0f; }

        updatedCharge = true;
    } else if (input.isKeyPressed(GLFW_KEY_DOWN)) {
        cpuCharge -= 0.1f;

        if (cpuCharge < 0.0f) { cpuCharge = 0.0f; }

        updatedCharge = true;
    }

    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::scale(transform, glm::vec3(scale, scale, scale));

    unsigned int transformLoc = glGetUniformLocation(shader.getProgram(), "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

    glUseProgram(shader.getProgram());
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
}

void Graphics::quit() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shader.getProgram());
}