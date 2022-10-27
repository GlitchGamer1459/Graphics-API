#include "Shader.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>

#include "utils/ErrorHandling.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

unsigned int Shader::s_BoundShader;

Shader::Shader(const std::string& filepath) :
    m_FilePath(filepath), m_RendererID(0)
{
    ShaderProgSrc shaders = ParseShader(m_FilePath);
    m_RendererID = CreateShader(shaders.vertexSrc, shaders.fragmentSrc);
}


Shader::~Shader() 
{
    GLCall(glDeleteProgram(m_RendererID));
}

// optimize to get cache locations at runtime
ShaderProgSrc Shader::ParseShader(const std::string& filepath) 
{
    std::ifstream stream(filepath);

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos) 
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
            ss[(int)type] << line << '\n';
    }

    return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CompileShader(const std::string& source, unsigned int type)
{
    GLCall(unsigned int id = glCreateShader(type));
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));

    if (result == GL_FALSE)
    {
        int len;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len));
        char* message = (char*)alloca(len * sizeof(char));
        GLCall(glGetShaderInfoLog(id, len, &len, message));

        std::cout << "[GLSL] " << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << " shader failed to compile\n";
        std::cout << message << std::endl;

        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}

unsigned int Shader::CreateShader(const std::string& VERTEX_SHADER, const std::string& FRAGMENT_SHADER) 
{
    GLCall(unsigned int program = glCreateProgram());
    unsigned int vs = CompileShader(VERTEX_SHADER, GL_VERTEX_SHADER);
    unsigned int fs = CompileShader(FRAGMENT_SHADER, GL_FRAGMENT_SHADER);

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}

void Shader::Bind() const 
{
    if (s_BoundShader != m_RendererID) 
    {
        GLCall(glUseProgram(m_RendererID));
        s_BoundShader = m_RendererID;
    }
}

void Shader::Unbind() const
{
    GLCall(glUseProgram(0));
    s_BoundShader = 0;
}

void Shader::SetUniform1i(const std::string& name, int value) 
{
    Bind();
    GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform1f(const std::string& name, float value) 
{
    Bind();
    GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) 
{
    Bind();
    GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix) 
{
    Bind();
    GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

int Shader::GetUniformLocation(const std::string& name) const 
{
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];

    GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));

    if (location == -1)
        std::cout << "[GLSL] Uniform " << name << " in \'" << m_FilePath
        << "\' does not exist, location: \'" << location << "\'" << std::endl;

    m_UniformLocationCache[name] = location;

    return location;
}