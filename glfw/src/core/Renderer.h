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

    typedef struct {
        float r;
        float g;
        float b;
        float a;
    } Color;

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
        static void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);

        static void DrawQuad(const float* data, const uint32_t dCount);
        static void DrawQuad(float x, float y, float w, float h, Color color);

        static void DrawBatch();

    };//Renderer2D

}//odin