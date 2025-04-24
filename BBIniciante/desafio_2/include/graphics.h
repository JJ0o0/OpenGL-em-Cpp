#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "shader.h"
#include "window.h"

class Graphics
{
private:
    Shader shader;

    unsigned int VAO, VBO;

    float vertices[8];
    float waterLevel = 1.0f; // 100%

    bool waterLevelChanged = false;
    bool pressed = false;

    void updateVertices();
    void changeWaterLevel(float newLevel);
    void changeColor(float yPos);
    void setupGraphics();
public:
    Graphics();
    
    bool init();

    void render(Window& window);
    void quit();
};

#endif