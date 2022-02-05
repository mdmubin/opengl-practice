#include "init.hpp"

#include <cstdlib>

#include <fmt/core.h>

void ogl::initGLFW(int versionMajor, int versionMinor)
{
    if (!glfwInit())
    {
        fmt::print(stderr, "FAILED TO INITIALIZE GLFW.");
        std::exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, versionMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, versionMinor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GLFWwindow *ogl::createGLContext(const char *title, int width, int height, bool resizable)
{
    // window creation
    if (!resizable)
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    auto window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window)
    {
        fmt::print(stderr, "Failed to initialize GLFW context.");
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glViewport(0, 0, width, height);

    // GLEW library initialization
    glewExperimental = GL_TRUE;
    auto glewStatus = glewInit();
    if (glewStatus != GLEW_OK)
    {
        fmt::print(stderr, "FAILED TO INITIALIZE GLEW. {}\n", glewGetErrorString(glewStatus));
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    return window;
}

void ogl::printInfo()
{
    // library information
    auto glfwVersion = glfwGetVersionString();
    auto glewVersion = glewGetString(GLEW_VERSION);
    auto shadingLanguageVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);

    // opengl information
    auto openglVendor = glGetString(GL_VENDOR);
    auto openglVersion = glGetString(GL_VERSION);
    auto openglRenderer = glGetString(GL_RENDERER);

    fmt::print(" {0:-^114}\n", "");

    fmt::print("| {0:<30}| {1:<80} |\n", "GLFW VERSION", glfwVersion);
    fmt::print("| {0:<30}| {1:<80} |\n", "GLEW VERSION", glewVersion);
    fmt::print("| {0:<30}| {1:<80} |\n", "SHADER LANGUAGE VERSION", shadingLanguageVersion);

    fmt::print("|{:-^114}|\n", "");

    fmt::print("| {0:<30}| {1:<80} |\n", "OPENGL VENDOR", openglVendor);
    fmt::print("| {0:<30}| {1:<80} |\n", "OPENGL VERSION", openglVersion);
    fmt::print("| {0:<30}| {1:<80} |\n", "OPENGL RENDERER", openglRenderer);

    fmt::print(" {0:-^114}\n\n\n", "");
}
