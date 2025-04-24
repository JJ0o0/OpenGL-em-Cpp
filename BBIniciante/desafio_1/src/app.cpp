#include <iostream>

#include "app.h"

App::App() : window(800, 600, "Sistema de Alerta Visual"), graphics() {}

bool App::init() {
    if (!window.init()) {
        std::cerr << "Falha ao inicializar a janela!" << std::endl;
        return false;
    }
    
    if (!graphics.init()) {
        std::cerr << "Falha ao inicializar gráficos!" << std::endl;
        return false;
    }

    return true;
}

void App::run() {
    while (!window.shouldClose()) {
        graphics.render(window);

        window.swapBuffers();
        window.pollEvents();
    }

    quit();
}

void App::quit() {
    graphics.quit();
    window.quit();
}