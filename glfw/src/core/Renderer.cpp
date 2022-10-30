#include "Renderer.h"

#include <iostream>

#include "utils/ErrorHandling.h"

namespace odin {

    static float s_ClearColor[4];

    Shader* Renderer2D::s_QuadShader;
    unsigned int Renderer2D::s_Count, Renderer2D::s_Size;

    std::vector<float> Renderer2D::s_Vertices;
    std::vector<unsigned int> Renderer2D::s_Indices;

    void Renderer2D::Init(const std::string& shaderName)
    {
        s_QuadShader = new Shader(shaderName);
    }

    void Renderer2D::Shutdown()
    {
        delete s_QuadShader;
    }

    void Renderer2D::Clear()
    {
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
    }

    void Renderer2D::SetClearColor(float r, float g, float b, float a)
    {
        s_ClearColor[0] = r;
        s_ClearColor[1] = g;
        s_ClearColor[2] = b;
        s_ClearColor[3] = a;

        GLCall(glClearColor(s_ClearColor[0], s_ClearColor[1], s_ClearColor[2], s_ClearColor[3]));
    }

    void Renderer2D::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)
    {
        shader.Bind();
        va.Bind();
        ib.Bind();

        GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
    }

    void Renderer2D::DrawQuad(const float* data, const uint32_t dCount, const uint32_t size,
        const uint32_t* indices, const uint32_t iCount)
    {
        for (int i = 0; i < dCount; i++) 
        {
            s_Vertices.push_back(*(data + i));
        }

        for (int i = 0; i < iCount; i++)
        {
            s_Indices.push_back(*(indices + i));
        }

        s_Size += size;
        s_Count += iCount;
    }

    void Renderer2D::DrawBatch()
    {
        VertexArray va;
        VertexBuffer vb(s_Vertices.data(), s_Size);
        VertexBufferLayout layout;
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(s_Indices.data(), s_Count);

        s_QuadShader->SetUniform4f("u_DQColor", 1.0f, 1.0f, 1.0f, 1.0f);

        Draw(va, ib, *s_QuadShader);
    }

}//odin