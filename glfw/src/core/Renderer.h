#pragma once

#include <GL/glew.h>

#include <iostream>
#include <string>
#include <vector>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

/*
 void DrawQuad
 void DrawTexQuad
 void DrawBatchedQuads
*/

namespace odin {

    struct Color {
        float r;
        float g;
        float b;
        float a;
    };

    class ConstColor
    {
    public:
        ConstColor(float ri, float gi, float bi, float ai)
            : c({ ri , gi, bi, ai })
        {
        }

        float r() { return c.r; };
        float b() { return c.g; };
        float g() { return c.b; };
        float a() { return c.a; };

    private:
        Color c;
    };

    class Colors
    {
    public:
        static ConstColor Black;
        static ConstColor White;
    };

    class Renderer2D {

    private:
        Renderer2D() = default;

        static Shader* s_QuadShader;
        static unsigned int s_Count, s_Size, s_QuadCount;

        static std::vector<float> s_Vertices;
        static std::vector<unsigned int> s_Indices;
        
    public:
        static void Init(const std::string& shaderName);
        static void Shutdown();

        static void Clear();
        static void SetClearColor(float r, float g, float b, float a);
        static void SetClearColor(Color color);
        static void SetClearColor(ConstColor color);
        static void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);

        static void DrawQuad(const float* data, const uint32_t dCount);
        static void DrawQuad(float x, float y, float w, float h, Color color);
        static void DrawQuad(float x, float y, float w, float h, ConstColor color);

        static void DrawBatch();

    };//Renderer2D

}//odin