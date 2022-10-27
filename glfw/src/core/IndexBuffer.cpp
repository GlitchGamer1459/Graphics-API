#include <GL/glew.h>

#include "utils/ErrorHandling.h"
#include "IndexBuffer.h"

namespace odin {

    unsigned int IndexBuffer::s_BoundBuffer;

    IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) :
        m_Count(count)
    {
        GLCall(glGenBuffers(1, &m_RendererID));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
        GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
    }

    IndexBuffer::~IndexBuffer()
    {
        GLCall(glDeleteBuffers(1, &m_RendererID));
    }

    void IndexBuffer::Bind() const
    {
        if (s_BoundBuffer != m_RendererID)
        {
            GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
            s_BoundBuffer = m_RendererID;
        }
    }

    void IndexBuffer::Unbind() const
    {
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
        s_BoundBuffer = 0;
    }

}