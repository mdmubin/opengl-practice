#include <string>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "rectangle.hpp"

#include "ogl/Init.hpp"
#include "ogl/shaders/Shader.hpp"


void tutorial::rectangle()
{
    ogl::initGLFW(4, 6);
    auto window = ogl::createGLContext("Rectangle Demo", 800, 800, true);
    ogl::printInfo();

    // rectangle data
    float vertices[4][3] = {
        { 0.5f,  0.5f,  0.0f},
        {-0.5f,  0.5f,  0.0f},
        {-0.5f, -0.5f,  0.0f},
        { 0.5f, -0.5f,  0.0f},
    };

    uint32_t indices[2][3] = {
        {0, 1, 2}, // 1st triangle index data
        {2, 3, 0}, // 2nd triangle index data
    };

    // create VAO
    uint32_t VAO{};
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    // create VBO
    uint32_t VBO{};
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // create EBO
    uint32_t EBO{};
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    // bind the rectangle data to the VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // bind the indices of the triangles to the EBO
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);
    // specify the data layout within the buffer
    glVertexAttribPointer(0, 3, GL_FLOAT, true, sizeof(float) * 3, nullptr);
    glEnableVertexAttribArray(0);

    // adding shaders
    std::string vertShaderFP = "assets/shaders/rectangle/default/vertexShader.vert";
    std::string fragShaderFP = "assets/shaders/rectangle/default/fragmentShader.frag";

    auto vertShader = ogl::shaderFromFile(vertShaderFP, GL_VERTEX_SHADER);
    auto fragShader = ogl::shaderFromFile(fragShaderFP, GL_FRAGMENT_SHADER);

    std::vector<uint32_t> shaders{vertShader, fragShader};

    // create shader program
    auto shaderProgram = ogl::createShaderProgram(shaders);
    // clean up after the shaders have been linked to the gl shader program
    for (auto shaderRef : shaders)
        glDeleteShader(shaderRef);

    glUseProgram(shaderProgram);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.3f, 0.2f, 0.8f, 1.0f);
        // clear background first
        glClear(GL_COLOR_BUFFER_BIT);
        // draw the shape
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}