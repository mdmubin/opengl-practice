#include <string>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "rectangle.hpp"

#include "ogl/Init.hpp"
#include "ogl/shaders/Shader.hpp"


void tutorial::shadedRectangle()
{
    ogl::initGLFW(4, 6);
    auto window = ogl::createGLContext("opengl window", 800, 800, true);
    ogl::printInfo();

    // rectangle data
    float vertices[4][3] = {
        { 0.5f,  0.5f,  0.0f},
        {-0.5f,  0.5f,  0.0f},
        {-0.5f, -0.5f,  0.0f},
        { 0.5f, -0.5f,  0.0f},
    };

    uint32_t indices[2][3] = {
        { 0, 1, 2},
        { 2, 3, 0},
    };

    uint32_t VAO{};
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    uint32_t VBO{};
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    uint32_t EBO{};
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, true, sizeof(float) * 3, nullptr);
    glEnableVertexAttribArray(0);

    std::string vertShaderFP = "assets/shaders/rectangle/shaded/vertexShader.vert";
    std::string fragShaderFP = "assets/shaders/rectangle/shaded/fragmentShader.frag";

    auto vertShader = ogl::shaderFromFile(vertShaderFP, GL_VERTEX_SHADER);
    auto fragShader = ogl::shaderFromFile(fragShaderFP, GL_FRAGMENT_SHADER);
    std::vector<uint32_t> shaders{vertShader, fragShader};

    auto shaderProgram = ogl::createShaderProgram(shaders);
    // clean up after the shaders have been linked to the gl shader program
    for (auto shaderRef : shaders)
        glDeleteShader(shaderRef);

    glUseProgram(shaderProgram);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.184f, 0.282f, 0.345f, 1.000f);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}