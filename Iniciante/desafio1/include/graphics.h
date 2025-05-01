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
    void updateColor();

    glm::vec3 currentColor = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 nextColor = currentColor;

    float transitionTime = 0.0f;

    bool inTransition = false;

    enum States { NORMAL, WARNING, CRITICAL };
    States currState = NORMAL; 
public:
    Graphics();
    
    bool init();

    void render(Window& window);
    void quit();
};

#endif