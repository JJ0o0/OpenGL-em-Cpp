#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
private:
    GLFWwindow* window;

    int width, height;
    const char* title;
public:
    Window(int width, int height, const char* title);

    bool init();
    bool shouldClose();
    bool getKey(int key, int action);

    void quit();
    void swapBuffers();
    void pollEvents();
};

#endif