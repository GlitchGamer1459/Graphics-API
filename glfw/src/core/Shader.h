#pragma once

#include <GL/glew.h>

#include <iostream>
#include <string>
#include <unordered_map>

#include "glm/glm.hpp"

namespace odin {

    struct ShaderProgSrc {

        std::string vertexSrc;
        std::string fragmentSrc;

    };

    class Shader {

    private:
        std::string m_FilePath;
        unsigned int m_RendererID;
        mutable std::unordered_map<std::string, int> m_UniformLocationCache;

    public:
        static unsigned int s_BoundShader;

        Shader(const std::string& filepath);
        ~Shader();

        void Bind() const;
        void Unbind() const;

        // set uniforms
        void SetUniform1i(const std::string& name, int value);
        void SetUniform1f(const std::string& name, float value);
        void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
        void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

    private:
        ShaderProgSrc ParseShader(const std::string& filepath);
        unsigned int CompileShader(const std::string& SOURCE, unsigned int type);
        unsigned int CreateShader(const std::string& VERTEX_SHADER, const std::string& FRAGMENT_SHADER);

        int GetUniformLocation(const std::string& name) const;

    };

}