#include <stdexcept>
#include <map>
#include <chrono>
#include <iostream>
#include "Application.h"
#include "GLFW/glfw3.h"
#include "Renderer.h"
#include "../World.h"

namespace {
    std::map<GLFWwindow*, Renderer*> windowsToRenders;

    void scrollCallback(GLFWwindow* window, double /*xoffset*/, double yoffset) {
        try {
            windowsToRenders.at(window)->onZoom(yoffset);
        } catch (...) {} // suppress possible exceptions
    }

    void registerScrollCallback(Renderer* renderer) {
        GLFWwindow* context = renderer->context();
        windowsToRenders[context] = renderer;
        glfwSetScrollCallback(context, scrollCallback);
    }
}

Application::Application(const char* name) {
    if (!glfwInit()) {
        throw std::logic_error("...");
    }
    renderer = std::make_unique<Renderer>(name);
    registerScrollCallback(renderer.get());
}

Application::~Application() {
    renderer.reset();
    glfwTerminate();
}

void Application::run(World& world) {
    time = std::chrono::system_clock::now();
    double totalTime = 0.;

    while (!renderer->shouldClose()) {
        // Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

        const auto currentTime = std::chrono::system_clock::now();
        const double delta = std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - time).count();
        time = currentTime;

        totalTime += delta;

        if (totalTime < 10.) {
            world.update(delta);
        }

        //std::cout << "FPS: " << 1. / delta << std::endl;

        Painter painter = renderer->getPainter();
        world.show(painter);
    }
}
