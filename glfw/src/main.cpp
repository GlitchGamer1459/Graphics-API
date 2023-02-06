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

using odin::Renderer2D;

int main(void)
{
    if (!OdinGlfwInit())
        return -1;

    odin::Window window(800, 800, "Hello World", NULL, NULL);
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

    Renderer2D::Init("res/shaders/DrawQuad.fs");
    Renderer2D::SetClearColor(odin::Colors::Black);

    while (!window.WindowShouldClose())
    {
        Renderer2D::Clear();
        
        float x = -1.0f;
        odin::ConstColor print_color = odin::Colors::Black;
        std::cout << "test" << print_color.r() << odin::Colors::Black.r() << std::endl;
        bool print_black = false;

        for (int dx = 0; dx < 8; dx++)
        {
            float y = -1.0f;

            for (int dy = 0; dy < 8; dy++)
            {
                Renderer2D::DrawQuad(x, y, 0.5f, 0.5f, print_color);

                if (print_black)
                    print_color = odin::Colors::Black;
                else
                    print_color = odin::Colors::White;

                print_black = !print_black;

                y += 0.25f;
            }

            print_black = !print_black;

            x += 0.25f;
        }

        Renderer2D::DrawBatch();
        window.SwapBuffers();
        glfwPollEvents();
    }

    return 0;
}