#include "cube.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

#include "ogl/Init.hpp"
#include "ogl/shaders/Shader.hpp"

void tutorial::cube()
{
    ogl::initGLFW(4, 6);
    auto window = ogl::createGLContext("Colored Cube Demo", 800, 800, false);
    ogl::printInfo();

    // from opengl-tutorial.org/beginners-tutorials/tutorial-4-a-colored-cube
    float cubeVertices[] = {
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
    };

    uint32_t VAO{};
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    uint32_t CubeBuffer{};
    glGenBuffers(1, &CubeBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, CubeBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 3, reinterpret_cast<void *>(0));
    glEnableVertexAttribArray(0);

    // from opengl-tutorial.org/beginners-tutorials/tutorial-4-a-colored-cube
    float cubeColors[] = {
        0.583f,  0.771f,  0.014f,
        0.609f,  0.115f,  0.436f,
        0.327f,  0.483f,  0.844f,
        0.822f,  0.569f,  0.201f,
        0.435f,  0.602f,  0.223f,
        0.310f,  0.747f,  0.185f,
        0.597f,  0.770f,  0.761f,
        0.559f,  0.436f,  0.730f,
        0.359f,  0.583f,  0.152f,
        0.483f,  0.596f,  0.789f,
        0.559f,  0.861f,  0.639f,
        0.195f,  0.548f,  0.859f,
        0.014f,  0.184f,  0.576f,
        0.771f,  0.328f,  0.970f,
        0.406f,  0.615f,  0.116f,
        0.676f,  0.977f,  0.133f,
        0.971f,  0.572f,  0.833f,
        0.140f,  0.616f,  0.489f,
        0.997f,  0.513f,  0.064f,
        0.945f,  0.719f,  0.592f,
        0.543f,  0.021f,  0.978f,
        0.279f,  0.317f,  0.505f,
        0.167f,  0.620f,  0.077f,
        0.347f,  0.857f,  0.137f,
        0.055f,  0.953f,  0.042f,
        0.714f,  0.505f,  0.345f,
        0.783f,  0.290f,  0.734f,
        0.722f,  0.645f,  0.174f,
        0.302f,  0.455f,  0.848f,
        0.225f,  0.587f,  0.040f,
        0.517f,  0.713f,  0.338f,
        0.053f,  0.959f,  0.120f,
        0.393f,  0.621f,  0.362f,
        0.673f,  0.211f,  0.457f,
        0.820f,  0.883f,  0.371f,
        0.982f,  0.099f,  0.879f
    };

    uint32_t ColorBuffer{};
    glGenBuffers(1, &ColorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, ColorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeColors), cubeColors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, 0, reinterpret_cast<void *>(0));
    glEnableVertexAttribArray(1);

    std::string vertShaderFP = "assets/shaders/cube/default/vertexShader.vert";
    std::string fragShaderFP = "assets/shaders/cube/default/fragmentShader.frag";

    auto vertShader = ogl::shaderFromFile(vertShaderFP, GL_VERTEX_SHADER);
    auto fragShader = ogl::shaderFromFile(fragShaderFP, GL_FRAGMENT_SHADER);

    std::vector<uint32_t> shaders{vertShader, fragShader};

    auto shaderProgram = ogl::createShaderProgram(shaders);

    for (auto shaderRef : shaders) glDeleteShader(shaderRef);

    glUseProgram(shaderProgram);

    // Z Buffer Fix. Enables Closer Objects to be rendered above further ones
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // transformation matrix for rotating cube
    auto transform = glm::mat4(1.0f);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(.1f, .1f, .1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        // changing the transform matrix through the x, y & z axes by 0.5 degree
        transform = glm::rotate(transform, glm::radians(0.5f), glm::vec3(1.0f, 1.0f, 1.0f));
        // passing transform matrix to the shader to update the cube rotation
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "transformMat"), 1, false, glm::value_ptr(transform));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}
