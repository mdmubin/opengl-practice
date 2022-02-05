#pragma once

#include <string>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace ogl
{

    /**
     * @brief Create a shader from a given shader source string and return a gl
     * reference to that shader object.
     * 
     * @param shaderSource shader source as a string
     * 
     * @param shaderType expects a GLenum value within GL_VERTEX_SHADER,
     * GL_FRAGMENT_SHADER or GL_GEOMETRY_SHADER.
     * 
     * @return gl reference to the the shader object 
     */
    uint32_t shaderFromSource(const std::string &shaderSource, GLenum shaderType);

    /**
     * @brief Create a shader using the contents within a file on the specified
     * filepath and return a gl reference to that shader object.
     * 
     * @param filepath path to the file
     * 
     * @param shaderType expects a GLenum value within GL_VERTEX_SHADER,
     * GL_FRAGMENT_SHADER or GL_GEOMETRY_SHADER.
     * 
     * @return gl reference to the shader object
     */
    uint32_t shaderFromFile(std::string &filepath, GLenum shaderType);

    /**
     * @brief Create a gl shader program by linking shaders present in the
     * vector and and return the gl reference to that shader program object.
     * 
     * @note This function does not clean up the shaders after linking to the
     * gl program and it expects all the shaders within the vector to be
     * pre-compiled.
     * 
     * @param compiledShaders a std::vector containing gl references to the
     * shader objects.
     * 
     * @return gl reference to the created shader program
     */
    uint32_t createShaderProgram(std::vector<uint32_t> &compiledShaders);

}
