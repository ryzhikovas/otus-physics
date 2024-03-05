cmake_minimum_required(VERSION 3.14)
project(physics)
include(FetchContent)

set(CMAKE_CXX_STANDARD 17)

# Пытаемся найти предустановленный SFML
find_package(SFML COMPONENTS graphics)

if (SFML_FOUND)
    message(STATUS "The SFML installed in the system will be used")
else ()
    # Если SFML не найден - выкачиваем и собираем из исходников
    message(STATUS "Get SFML from the source code")
    FetchContent_Declare(SFML
            GIT_REPOSITORY https://github.com/SFML/SFML.git
            GIT_TAG 2.6.x)
    set(SFML_BUILD_AUDIO OFF CACHE BOOL "" FORCE)
    set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
    # Обход потенциальных проблем при сборке sfml-graphics
    # (stb_image.h: 'argument': conversion from 'int' to 'short')
    set(WARNINGS_AS_ERRORS FALSE CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(SFML)
endif ()

if (SFML_FOUND AND NOT FORCE_GIF)
    message(STATUS "Use SFML ui")
    add_library(ui STATIC black_box/sfml/Application.cpp black_box/sfml/View.cpp black_box/sfml/SFMLPainter.cpp)
    target_link_libraries(ui PUBLIC sfml-graphics)
    target_include_directories(ui INTERFACE black_box/sfml)
else ()
    message(STATUS "Use GIF render")
    FetchContent_Declare(msf_gif
            GIT_REPOSITORY https://github.com/notnullnotvoid/msf_gif.git
            GIT_TAG 7829c8f439d013deeb54eba94761403e1da2a960)
    FetchContent_MakeAvailable(msf_gif)

    add_library(ui STATIC black_box/gif/Application.cpp black_box/gif/GifPainter.cpp black_box/gif/Image.cpp)
    target_include_directories(ui PUBLIC ${msf_gif_SOURCE_DIR})
    target_include_directories(ui INTERFACE black_box/gif)
endif ()



# К сожалению, вплоть до C++20 https://en.cppreference.com/w/cpp/numeric/constants
# нет удобного кроссплатформенного способа получить число pi.
# define ниже нужен для включения M_PI
if (MSVC)
    add_definitions(-D_USE_MATH_DEFINES)
endif ()

add_executable(physics main.cpp World.cpp Ball.cpp Physics.cpp Color.cpp)
target_link_libraries(physics PRIVATE ui)

target_compile_options(physics PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
        )
