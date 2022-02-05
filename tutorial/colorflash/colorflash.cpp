#include <chrono>
#include <iostream>

#include <fmt/core.h>
#include <fmt/color.h>
#include <fmt/format.h>

#include <glm/vec4.hpp>

#include "ogl/Init.hpp"
#include "colorflash.hpp"

// chrono aliases
using timer = std::chrono::steady_clock;
using duration = std::chrono::duration<double>;

void tutorial::flash()
{
    auto startTime = timer::now();

    ogl::initGLFW(4, 6);
    auto window = ogl::createGLContext("opengl window", 1280, 720, true);
    ogl::printInfo();

    glm::vec4 clearColour {0};

    while (!glfwWindowShouldClose(window))
    {
        auto currentTime = duration(timer::now() - startTime).count();
        clearColour = {
            (float)std::sin(currentTime) * 0.5f + 0.5f,
            (float)std::cos(currentTime) * 0.5f + 0.5f,
            0.2f,
            1.0f,
        };

        glClearBufferfv(GL_COLOR, 0, &clearColour[0]);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}