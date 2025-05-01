#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "shader.h"
#include "window.h"

class Graphics
{
private:
    Shader shader;

    unsigned int VAO, VBO, EBO;

    void setupGraphics();
public:
    Graphics();
    
    bool init();

    void render(Window& window);
    void quit();
};

#endif