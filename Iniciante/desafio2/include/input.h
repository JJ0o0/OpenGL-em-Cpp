#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>

class Input
{
public:
    void onKey(int key, int scanCode, int action, int mods);
    void onMouseMove(double xpos, double ypos);
    void onScroll(double xoffest, double yoffset);

    bool isKeyPressed(int key) const;
    double getScrollOffsetY() const;
private:
    bool keys[1024] = { false };

    double mouseX = 0.0, mouseY = 0.0;
    double scrollY = 0.0;
};

#endif