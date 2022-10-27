#include "VertexArray.h"

#include "utils/ErrorHandling.h"

namespace odin {

    unsigned int VertexArray::s_BoundBuffer;

    VertexArray::VertexArray()
    {
        GLCall(glGenVertexArrays(1, &m_RendererID));
        GLCall(glBindVertexArray(m_RendererID));
    }

    VertexArray::~VertexArray()
    {
        GLCall(glDeleteVertexArrays(1, &m_RendererID));
    }

    void VertexArray::Bind() const
    {
        if (s_BoundBuffer != m_RendererID)
        {
            GLCall(glBindVertexArray(m_RendererID));
            s_BoundBuffer = m_RendererID;
        }
    }

    void VertexArray::Unbind() const
    {
        GLCall(glBindVertexArray(0));
        s_BoundBuffer = 0;
    }

    void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
    {
        Bind();
        vb.Bind();
        const auto& elements = layout.GetElements();
        unsigned int offset = 0;

        for (unsigned int i = 0; i < elements.size(); i++)
        {
            const auto& element = elements[i];
            GLCall(glEnableVertexAttribArray(i));
            GLCall(glVertexAttribPointer(i, element.count, element.type,
                element.normalized, layout.GetStride(), (const void*)offset));
            offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
        }
    }

}