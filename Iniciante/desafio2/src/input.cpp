#include "input.h"

void Input::onKey(int key, int scanCode, int action, int mods) {
    if (key >= 0 && key < 1024) {
        keys[key] = (action != GLFW_RELEASE);
    }
}

void Input::onMouseMove(double xpos, double ypos) {
    mouseX = xpos;
    mouseY = ypos;
}

void Input::onScroll(double xoffset, double yoffset) {
    scrollY = yoffset;
}

bool Input::isKeyPressed(int key) const {
    return keys[key];
}

double Input::getScrollOffsetY() const {
    return scrollY;
}