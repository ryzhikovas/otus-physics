#include "glfwWrapper.h"
#include <optional>
#include <string>
#include <stdexcept>

namespace impl {
    std::optional<std::pair<int, std::string>> lastError;

    void onGLFWError(int code, const char* message) {
        lastError.emplace(code, message);
    }

    void throwOnError() {
        if (lastError) {
            auto [code, message] = lastError.value();
            lastError.reset();
            throw std::runtime_error("GLFW error. Code " + std::to_string(code) + ". " + message);
        }
    }
}


