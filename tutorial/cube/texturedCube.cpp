#include "cube.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

#include <fmt/core.h>

#include "ogl/Init.hpp"
#include "ogl/shaders/Shader.hpp"

#include "utils/Constants.hpp"
#include "utils/Image.hpp"

void tutorial::texturedCube()
{
    ogl::initGLFW(4, 6);
    auto window = ogl::createGLContext("Textured Cube Demo", myutils::SCREEN_WIDTH, myutils::SCREEN_HEIGHT, false);
    ogl::printInfo();

    float cubeVertices[] = {
        // VERTEX               // TEXTURE
        -0.5f, -0.5f, -0.5f,    0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,    1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,    1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,    1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,    0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,    0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,    0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,    1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,    1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,    1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,    0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,    0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,    1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,    1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,    0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,    1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,    1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,    1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,    0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,    0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,    0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,    1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,    1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,    1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,    1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,    0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,    0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,    1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,    1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,    1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,    0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,    0.0f, 1.0f,
    };

    uint32_t VAO{};
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    uint32_t cubeBuffer{};
    glGenBuffers(1, &cubeBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, cubeBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_DYNAMIC_DRAW);
    // cubeCoordinates
    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 5, reinterpret_cast<void *>(0));
    glEnableVertexAttribArray(0);
    // textureCoordinates
    glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(float) * 5, reinterpret_cast<void *>(sizeof(float) * 3));
    glEnableVertexAttribArray(1);

    // SHADER HANDLING
    std::string vertShaderFP = "assets/shaders/cube/textured/vertexShader.vert";
    std::string fragShaderFP = "assets/shaders/cube/textured/fragmentShader.frag";

    auto vertShader = ogl::shaderFromFile(vertShaderFP, GL_VERTEX_SHADER);
    auto fragShader = ogl::shaderFromFile(fragShaderFP, GL_FRAGMENT_SHADER);

    std::vector<uint32_t> shaders{vertShader, fragShader};
    auto shaderProgram = ogl::createShaderProgram(shaders);
    for (auto shaderRef : shaders) glDeleteShader(shaderRef);

    // TEXTURE HANDLING
    uint32_t cubeTexture1{};
    glGenTextures(1, &cubeTexture1);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, cubeTexture1);

    std::string texture1Path = "assets/images/wall.jpg";

    auto image1 = myutils::Image(texture1Path, false);
    if (image1)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image1.width(), image1.height(), 0, GL_RGB,
                     GL_UNSIGNED_BYTE, image1.imageData());
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    uint32_t cubeTexture2{};
    glGenTextures(1, &cubeTexture2);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, cubeTexture2);

    std::string texture2Path = "assets/images/triangle.jpg";

    auto image2 = myutils::Image(texture2Path, false);
    if (image2)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image2.width(), image2.height(), 0, GL_RGB,
                     GL_UNSIGNED_BYTE, image2.imageData());
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    glUseProgram(shaderProgram);
    // Z Buffer Fix. Enables Closer Objects to be rendered above further ones
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // set sampler
    glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
    glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1);

    auto model      = glm::mat4(1.0f);
    auto view       = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -2.5f));
    auto projection = glm::perspective(glm::radians(45.0f), (float) myutils::SCREEN_WIDTH / (float) myutils::SCREEN_HEIGHT, 0.001f, 100.0f);

    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, false, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, false, glm::value_ptr(view));

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(.1f, .1f, .1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        model = glm::rotate(model, glm::radians(0.5f), glm::vec3(1.0f, 1.0f, 1.0f));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, false, glm::value_ptr(model));

        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
