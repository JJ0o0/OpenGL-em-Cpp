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
    void updateCPUCharge();
    void updateColor();

    float scale = 1.0f;
    float cpuCharge = 100.0f;

    bool updatedCharge = false;

    glm::vec3 interpolatedColor;
public:
    Graphics();
    
    bool init();

    void render(Window& window);
    void quit();
};

#endif