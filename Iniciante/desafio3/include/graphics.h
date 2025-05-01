#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "shader.h"
#include "window.h"

#include <glm/glm.hpp>

class Graphics
{
private:
    Shader shader;

    unsigned int VAO, VBO, EBO;

    void setupGraphics();

    float scale = 1.0f;
    glm::vec2 pos = glm::vec2(0.0f, 0.0f);
public:
    Graphics();
    
    bool init();

    void render(Window& window);
    void quit();
};

#endif