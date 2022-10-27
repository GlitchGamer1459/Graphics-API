#include "VertexBuffer.h"

#include "utils/ErrorHandling.h"

unsigned int VertexBuffer::s_BoundBuffer;

VertexBuffer::VertexBuffer(const void* data, unsigned int size) 
{
    GLCall(glGenBuffers(1, &m_RendererID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer() 
{
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::Bind() const 
{
    if (s_BoundBuffer != m_RendererID) 
    {
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
        s_BoundBuffer = m_RendererID;
    }
}

void VertexBuffer::Unbind() const 
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    s_BoundBuffer = 0;
}