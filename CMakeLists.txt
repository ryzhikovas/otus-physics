cmake_minimum_required(VERSION 3.7.2)
project(physics)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw
    GIT_TAG        3.3.8
)
FetchContent_Populate(glfw)
# Make subproject to use 'BUILD_SHARED_LIBS=ON' setting.
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF INTERNAL)
add_subdirectory(${glfw_SOURCE_DIR})

find_package(OpenGL REQUIRED)


# К сожалению, вплоть до C++20 https://en.cppreference.com/w/cpp/numeric/constants
# нет удобного кроссплатформенного способа получить число pi.
# define ниже нужен для включения M_PI
if(MSVC)
    add_definitions(-D_USE_MATH_DEFINES)
endif()

add_executable(physics main.cpp World.cpp World.h black_box/Renderer.cpp black_box/Renderer.h black_box/Application.cpp black_box/Application.h Painter.cpp
        Painter.h Point.h black_box/Screen.cpp black_box/Screen.h black_box/View.cpp black_box/Zoomable.h Color.h Color.cpp Ball.cpp Ball.hpp Velocity.h black_box/PainterImpl.cpp black_box/PainterImpl.h Physics.cpp Physics.h black_box/glfwWrapper.cpp black_box/glfwWrapper.h)
target_link_libraries(physics glfw OpenGL::GL)
