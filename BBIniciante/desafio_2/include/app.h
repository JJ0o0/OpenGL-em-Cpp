#ifndef APP_H
#define APP_H

#include "window.h"
#include "graphics.h"

class App
{
private:
    Window window;
    Graphics graphics;
public:
    App();
    
    bool init();

    void run();
    void quit();
};

#endif