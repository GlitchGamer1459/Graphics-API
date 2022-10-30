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

    class Renderer2D {

    private:
        Renderer2D() = default;

        static Shader* s_QuadShader;
        static unsigned int s_Count, s_Size;

        static std::vector<float> s_Vertices;
        static std::vector<unsigned int> s_Indices;
        
    public:
        static void Init(const std::string& shaderName);
        static void Shutdown();

        static void Clear();
        static void SetClearColor(float r, float g, float b, float a);
        static void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);

        static void DrawQuad(const float* data, const uint32_t dCount, const uint32_t size, 
            const uint32_t* indices, const uint32_t iCount);

        static void DrawBatch();

    };//Renderer2D

}//odin