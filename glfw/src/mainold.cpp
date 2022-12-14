#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include <windows.h>

#include "utils/ErrorHandling.h"
#include "core/Display.h"
#include "core/Renderer.h"
#include "core/VertexBuffer.h"
#include "core/IndexBuffer.h"
#include "core/VertexArray.h"
#include "core/Shader.h"
#include "core/Texture.h"
#include "utils/Queue.h"
#include "utils/Maths.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#define ODIN_RED { 1.0f, 0.0f, 0.0f, 1.0f }

using odin::Renderer2D;

int main(void)
{
    if (!glfwInit())
        return -1;

    glfwSetErrorCallback(GlfwErrorCallback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    odin::Window window(960, 540, "Hello World", NULL, NULL);
    if (window.WindowDoesNotExist())
    {
        std::cout << "glfw failed to make a window\n";
        return -1;
    }

    window.MakeContextCurrent();

    glfwSwapInterval(1);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return 1;
    }

    std::cout << "using OpenGL version " << glGetString(GL_VERSION) << std::endl;
    std::cout << "using GLFW version " << glfwGetVersionString() << std::endl;
    std::cout << "using GLEW version " << glewGetString(GLEW_VERSION) << std::endl;

    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GLCall(glEnable(GL_BLEND));

    float birdV[] = {
        -42.5f, -32.5f, 0.0f, 1.0f, // 0
        -42.5f,  32.5f, 0.0f, 0.0f, // 1
         42.5f,  32.5f, 1.0f, 0.0f, // 2
         42.5f, -32.5f, 1.0f, 1.0f  // 3 
    };

    unsigned int birdIndices[] = {
        0, 1, 2,
        2, 3, 0
    };

    odin::VertexArray bird;
    odin::VertexBuffer vb(&birdV, 4 * 4 * sizeof(float));
    odin::VertexBufferLayout birdLayout;
    birdLayout.Push<float>(2);
    birdLayout.Push<float>(2);
    bird.AddBuffer(vb, birdLayout);

    odin::IndexBuffer birdIB(birdIndices, 6);

    glm::vec3 birdTranslation(320, 270, 0);

    glm::mat4 projection = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

    odin::Shader birdShader("res/shaders/fbird.fs");

    odin::Texture texture("res/textures/flappy_bird.png");
    texture.Bind(0);
    birdShader.SetUniform1i("u_Texture", 0);

    float birdSpeed = 0.0f;

    Renderer2D::SetClearColor(0.25f, 0.95f, 1.0f, 1.0f);

    while (!window.WindowShouldClose())
    {
        Renderer2D::Clear();

        birdSpeed -= 0.25;

        birdTranslation.y += birdSpeed;

        if (GetAsyncKeyState(VK_SPACE) & 0x8000 && birdSpeed < 6)
            birdSpeed = 8;

        glm::mat4 model = glm::translate(glm::mat4(1.0f), birdTranslation);

        glm::mat4 mvp = projection * view * model;

        birdShader.SetUniformMat4f("u_bMVP", mvp);
        Renderer2D::Draw(bird, birdIB, birdShader);

        window.SwapBuffers();
        glfwPollEvents();
    }

    return 0;
}