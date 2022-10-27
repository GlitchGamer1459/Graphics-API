#include "Renderer.h"

#include <iostream>

#include "utils/ErrorHandling.h"

void Renderer::Clear() const 
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::SetClearColor(float r, float g, float b, float a) 
{
    m_ClearColor[0] = r;
    m_ClearColor[1] = g;
    m_ClearColor[2] = b;
    m_ClearColor[3] = a;

    GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) 
{
    shader.Bind();
    va.Bind();
    ib.Bind();

    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}