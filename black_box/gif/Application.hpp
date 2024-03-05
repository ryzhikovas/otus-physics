#pragma once
#include "Image.hpp"
#include "msf_gif.h"

class World;

class Application {
  public:
    Application(const char* name);
    void run(World& world);
  private:
    Image buffer;
    MsfGifState gif;
};
