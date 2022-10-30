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
    if (!OdinGlfwInit())
        return -1;

    odin::Window window(960, 540, "Hello World", NULL, NULL);
    if (window.WindowDoesNotExist()) 
    {
        std::cout << "glfw failed to make a window\n";
        return -1;
    }

    window.MakeContextCurrent();

    if (!OdinGlewInit())
        return -1;

    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GLCall(glEnable(GL_BLEND));

    glm::mat4 projection = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

    float square[]{
        0, 0, // 0
        0, 1, // 1
        1, 1, // 2
        1, 0  // 3 
    };

    float s2[]{
        0, 0, // 4
        0, -1, // 5
        -1, -1, // 6
        -1, 0  // 7 
    };

    Renderer2D::Init("res/shaders/DrawQuad.fs");
    Renderer2D::SetClearColor(0.25f, 0.95f, 1.0f, 1.0f);

    while (!window.WindowShouldClose())
    {
        Renderer2D::Clear();

        Renderer2D::DrawQuad(square, 8);
        Renderer2D::DrawQuad(s2, 8);

        Renderer2D::DrawBatch();
        window.SwapBuffers();
        glfwPollEvents();
    }

    return 0;
}