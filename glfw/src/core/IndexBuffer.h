#pragma once

#include <GL/glew.h>

namespace odin {

    class IndexBuffer {

    private:
        unsigned int m_RendererID;
        unsigned int m_Count;

    public:
        static unsigned int s_BoundBuffer;

        IndexBuffer(const unsigned int* data, unsigned int count);
        ~IndexBuffer();

        void Bind() const;
        void Unbind() const;

        inline unsigned int GetCount() const { return m_Count; }

    };

}