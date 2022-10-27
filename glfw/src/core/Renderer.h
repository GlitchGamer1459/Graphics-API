#pragma once

#include <GL/glew.h>

#include <iostream>
#include <string>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

/*
 void DrawQuad
 void DrawTexQuad
 void DrawQueue
*/

namespace odin {

    enum RGBA : unsigned char {

        Red = 0x00,
        Orange = 0x01,
        Yellow = 0x02,
        Green = 0x03,
        Blue = 0x04,
        Purple = 0x05,
        White = 0x06,
        Black = 0x07,
        Gray = 0x08

    };

    struct Color {

        float r;
        float g;
        float b;
        float a;

    };

    class Renderer {

    private:
        float m_ClearColor[4];

    public:
        void Clear() const;
        void SetClearColor(float r, float g, float b, float a);
        void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);

    };

}