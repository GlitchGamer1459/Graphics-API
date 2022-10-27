#pragma once

#include <GL/glew.h>

class VertexBuffer {

private:
    unsigned int m_RendererID;

public:
    static unsigned int s_BoundBuffer;

    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;

};