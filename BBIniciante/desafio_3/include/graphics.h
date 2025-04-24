#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "shader.h"
#include "window.h"

class Graphics
{
private:
    Shader shader;

    GLuint VAO, VBO, EBO;

    bool paused = false;

    void setupGraphics();
public:
    Graphics();
    
    bool init();

    void render(Window& window);
    void quit();
};

#endif