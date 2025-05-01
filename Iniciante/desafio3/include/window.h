#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "input.h"

class Window
{
private:
    GLFWwindow* window;
    Input input;

    int width, height;
    const char* title;

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
public:
    Window(int width, int height, const char* title);

    bool init();
    bool shouldClose();

    void quit();
    void swapBuffers();
    void pollEvents();

    GLFWwindow* getGLFWWindow() const;
    Input& getInput();
};

#endif