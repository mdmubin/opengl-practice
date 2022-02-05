#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace tutorial
{
    /**
     * @brief Run the OpenGL basic rectangle demo
     */
    void rectangle();

    /**
     * @brief Run the OpenGL shaded rectangle demo
     * 
     * @note this demo code is absolutely the same as the simple rectangle demo.
     * with the only difference being the different shaders being used.
     */
    void shadedRectangle();
}