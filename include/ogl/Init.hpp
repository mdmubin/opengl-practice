#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace ogl
{
    /**
     * @brief Initialize GLFW with the given OpenGL version
     */
    void initGLFW(int versionMajor, int versionMinor);

    /**
     * @brief Create an OpenGL Context (OpenGL window) with the given window
     * settings.
     *
     * @note only to be called after calling intiGLFW
     *
     * @return Reference to an OpenGL context
     */
    GLFWwindow *createGLContext(const char *title, int width, int height, bool resizable);

    /**
     * @brief Print relevant OpenGL Information to stdout.
     */
    void printInfo();
}
