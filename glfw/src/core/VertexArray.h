#pragma once

#include <GL/glew.h>

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace odin {

    class VertexArray {

    private:
        unsigned int m_RendererID;

    public:
        static unsigned int s_BoundBuffer;

        VertexArray(const VertexArray&) = delete;

        VertexArray();
        ~VertexArray();

        void Bind() const;
        void Unbind() const;

        void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

    };

}