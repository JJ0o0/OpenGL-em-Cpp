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
         0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };

    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3
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

void Graphics::updateColor() {
    switch (currState)
    {
        case NORMAL:
            nextColor = glm::vec3(0.0f, 1.0f, 0.0f);
            break;
        case WARNING:
            nextColor = glm::vec3(1.0f, 1.0f, 0.0f);
            break;
        case CRITICAL:
            nextColor = glm::vec3(1.0f, 0.0f, 0.0f);
            break;
    }
    
    transitionTime = glfwGetTime();
    inTransition = true;
}

void Graphics::render(Window& window) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    Input input = window.getInput();
    if (input.isKeyPressed(GLFW_KEY_1)) {
        currState = NORMAL;
    } else if (input.isKeyPressed(GLFW_KEY_2)) {
        currState = WARNING;
    } else if (input.isKeyPressed(GLFW_KEY_3)) {
        currState = CRITICAL;
    }

    static States lastState = currState;
    if (currState != lastState) {
        updateColor();

        lastState = currState;
    }
    
    float t = 1.0f;
    if (inTransition) {
        float time = glfwGetTime();

        t = (time - transitionTime) / 0.2f;
        if (t >= 1.0f) {
            t = 1.0f;

            currentColor = nextColor;

            inTransition = false;
        }
    }

    float colorLoc = glGetUniformLocation(shader.getProgram(), "ourColor");
    float nextColorLoc = glGetUniformLocation(shader.getProgram(), "nextColor");
    float timeLoc = glGetUniformLocation(shader.getProgram(), "progress");
    glUniform3fv(colorLoc, 1, &currentColor[0]);
    glUniform3fv(nextColorLoc, 1, &nextColor[0]);
    glUniform1f(timeLoc, t);

    float normalized_angle = fmod(glfwGetTime() * 1.0f, 2 * M_PI);

    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::rotate(transform, normalized_angle, glm::vec3(0.0f, 0.0f, 1.0f));

    unsigned int transformLoc = glGetUniformLocation(shader.getProgram(), "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

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