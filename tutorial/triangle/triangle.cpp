#include <string>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "triangle.hpp"

#include "ogl/Init.hpp"
#include "ogl/shaders/Shader.hpp"


void tutorial::triangle()
{
    ogl::initGLFW(4, 6);
    auto window = ogl::createGLContext("opengl window", 800, 800, true);
    ogl::printInfo();

    // triangle data
    float vertices[3][3] = {
        { 0.0f,  0.5f,  0.0f},
        {-0.5f, -0.5f,  0.0f},
        { 0.5f, -0.5f,  0.0f},
    };

    // create 1 vertex array object and bind to current gl context
    uint32_t VAO{};
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    // create 1 vertex buffer object and bind to current gl context
    uint32_t VBO{};
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // bind the triangle data to the buffer object
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // specify the data layout within the buffer
    glVertexAttribPointer(
        0,                    // starting index of your data
        3 ,                   // size of your data
        GL_FLOAT,             // type of your data
        true,                 // specify if the data is already normalized
        sizeof(float) * 3,    // how many bytes from 1 vertex to the the next
        nullptr               // I have no clue what this is....yet...
    );
    // enable the generated VAO.
    // In our case only 1 VAO has been generated, so enable the VAO at index 0.
    glEnableVertexAttribArray(0);

    // Adding shaders

    // vertex shader
    std::string vertShaderFP = "./assets/shaders/triangle/vertexShader.vert";
    auto vertShader = ogl::shaderFromFile(vertShaderFP, GL_VERTEX_SHADER);
    // fragment shader
    std::string fragShaderFP = "./assets/shaders/triangle/fragmentShader.frag";
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
        // draw the shape
        glDrawArrays(
            GL_TRIANGLES,    // draw mode
            0,               // first index to draw (from the buffer object)
            3                // number of vertices drawn
        );

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}
