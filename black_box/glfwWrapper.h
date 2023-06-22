#pragma once
#include "GLFW/glfw3.h"
#include <type_traits>

namespace impl {
    void onGLFWError(int code, const char* message);
    void throwOnError();

    template <class Fn, class... Args>
    static constexpr bool is_return_v = !std::is_same_v<std::invoke_result_t<Fn, Args...>, void>;
}

template <class Fn, class... Args, class Enable = std::enable_if_t<!impl::is_return_v<Fn, Args...>>>
void safeGLFWCall(Fn fn, Args... args) {
    auto prevCallback = glfwSetErrorCallback(impl::onGLFWError);
    fn(args...);
    glfwSetErrorCallback(prevCallback);
    impl::throwOnError();
}

template <class Fn, class... Args, class Enable = std::enable_if_t<impl::is_return_v<Fn, Args...>>>
auto safeGLFWCall(Fn fn, Args... args) {
    auto prevCallback = glfwSetErrorCallback(impl::onGLFWError);
    auto result = fn(args...);
    glfwSetErrorCallback(prevCallback);
    impl::throwOnError();
    return result;
}
