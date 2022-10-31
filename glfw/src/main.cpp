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

    odin::Shader birdShader("res/shaders/fbird.fs");

    odin::Texture texture("res/textures/flappy_bird.png");
    texture.Bind(0);
    birdShader.SetUniform1i("u_Texture", 0);

    float birdSpeed = 0.0f;
    bool hasBegun = false;
    bool hasPressed = false;
    
    float pipeB[]{
        0.3f, -0.3f, 0.0f,
        0.3f, -0.3f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f
    };

    Renderer2D::Init("res/shaders/DrawQuad.fs");
    Renderer2D::SetClearColor(0.25f, 0.95f, 1.0f, 1.0f);

    while (!window.WindowShouldClose())
    {
        Renderer2D::Clear();

        if (hasBegun)
        {
            birdSpeed -= 0.25;
            birdSpeed = util::clampf(birdSpeed, -20, 10);

            birdTranslation.y += birdSpeed;
        }

        short spaceState = GetAsyncKeyState(VK_SPACE);

        if (spaceState & 0x8000 && birdSpeed < 6 && !hasPressed)
        {
            birdSpeed = 8;
            if (!hasBegun)
                hasBegun = true;
            hasPressed = true;
        }
        else if ((spaceState & 0x8000) == 0x0000)
        {
            hasPressed = false;
        }

        float degrees = 4 * birdSpeed;

        glm::mat4 model = glm::translate(glm::mat4(1.0f), birdTranslation);
        model = glm::rotate(model, glm::radians(util::clampf(degrees, -60.0f, 70.0f)), glm::vec3(0, 0, 1));

        glm::mat4 mvp = projection * view * model;
        
        birdShader.SetUniformMat4f("u_bMVP", mvp);

        if (!(birdTranslation.y < 108.0f + 32.5f))
            Renderer2D::Draw(bird, birdIB, birdShader);
        else
            return 0;
        
        //ground
        Renderer2D::DrawQuad(-1.0f, -1.0f, 2.0f, 0.4f, {0.15f, 0.6f, 0.1f, 1.0f});

        Renderer2D::DrawBatch();
        window.SwapBuffers();
        glfwPollEvents();
    }

    return 0;
}