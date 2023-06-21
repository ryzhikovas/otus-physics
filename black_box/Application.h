#pragma once
#include <memory>
#include <chrono>

class World;
class Renderer;

class Application {
public:
    Application(const char* name);
    ~Application();
    void run(World& world);
private:
    std::unique_ptr<Renderer> renderer;
    std::chrono::system_clock::time_point time;
};
