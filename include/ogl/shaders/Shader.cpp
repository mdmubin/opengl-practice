#include "Shader.hpp"
#include "utils/FileIO.hpp"

#include <fmt/core.h>

// forward declarations

void verifyShader(uint32_t shaderRef);
void verifyProgram(uint32_t programRef);

// shader compilations

uint32_t ogl::shaderFromSource(const std::string &shaderSource, GLenum shaderType)
{
    auto shader = glCreateShader(shaderType);

    auto cstr = shaderSource.c_str();
    glShaderSource(shader, 1, &cstr, nullptr);
    glCompileShader(shader);
    verifyShader(shader);

    return shader;
}

uint32_t ogl::shaderFromFile(std::string &filepath, GLenum shaderType)
{
    return ogl::shaderFromSource(myutils::readFileContents(filepath), shaderType);
}

// shader error logging

void verifyShader(uint32_t shaderRef)
{
    int success;
    glGetShaderiv(shaderRef, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        char log[1024];
        glGetShaderInfoLog(shaderRef, 1024, nullptr, log);
        fmt::print(stderr, "FAILED TO COMPILE SHADER:\n{}\n", log);
    }
}

// shader program linking

uint32_t ogl::createShaderProgram(std::vector<uint32_t> &compiledShaders)
{
    auto program = glCreateProgram();
    for (auto shader : compiledShaders) { glAttachShader(program, shader); }
    glLinkProgram(program);
    verifyProgram(program);
    return program;
}

// shader program error logging

void verifyProgram(uint32_t programRef)
{
    int success;
    glGetProgramiv(programRef, GL_LINK_STATUS, &success);

    if (!success)
    {
        char log[1024];
        glGetProgramInfoLog(programRef, 1024, nullptr, log);
        fmt::print(stderr, "FAILED TO LINK PROGRAM:\n{}\n", log);
    }
}
