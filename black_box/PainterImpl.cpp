#include <cmath>
#include "PainterImpl.h"

PainterImpl::PainterImpl(GLFWwindow *window, const View &view)
    :window{window} {
    glClearColor(0.f, 0.f, 0.f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    int width{};
    int height{};
    glfwGetWindowSize(window, &width, &height);
    glViewport(0, 0, width, height);

    screen = Screen(view, width, height);
}

PainterImpl::~PainterImpl() {
    // Swap the screen buffers
    glfwSwapBuffers(window);
}

void PainterImpl::draw(const Point& center, double radius, const Color& color) {
    glColor3d(color.red(), color.green(), color.blue());

    glBegin(GL_POLYGON);
    for (int i = 0; i <= 300; i++) {
        double angle = 2 * M_PI * i / 300;
        double x = std::cos(angle) * radius;
        double y = std::sin(angle) * radius;
        addVertex({center.x + x, center.y + y});
    }
    glEnd();
}

void PainterImpl::draw(const Point &topLeft, const Point &bottomRight, const Color& color) {
    glColor3d(color.red(), color.green(), color.blue());

    glBegin(GL_QUADS);
    {
        addVertex(topLeft);
        addVertex({bottomRight.x, topLeft.y});
        addVertex(bottomRight);
        addVertex({topLeft.x, bottomRight.y});
    }
    glEnd();
}

void PainterImpl::addVertex(const Point &pos) {
    const Point screenPos = screen.toScreen(pos);
    glVertex2d(screenPos.x, screenPos.y);
}
