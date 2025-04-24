#include <iostream>

#include "window.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

Window::Window(int width, int height, const char* title) : width(width), height(height), title(title), window(nullptr) {}

bool Window::init() {
    if (!glfwInit()) {
        std::cerr << "GLFW - Falha ao inicializar!" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(
        width, height,
        title,
        NULL, NULL
    );

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "GLAD - Falha ao carregar!" << std::endl;
        glfwTerminate();

        return false;
    }
    
    return true;
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(window);
}

bool Window::getKey(int key, int action) {
    int state = glfwGetKey(window, key);

    return state == action;
}

void Window::swapBuffers() {
    glfwSwapBuffers(window);
}

void Window::quit() {
    glfwTerminate();
}

void Window::pollEvents() {
    glfwPollEvents();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}