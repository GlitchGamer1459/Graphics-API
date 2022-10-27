#include "ErrorHandling.h"

void GlfwErrorCallback(int code, const char* errmsg) 
{
    std::cout << "[GLFW Error] (" << code << "): " << errmsg << std::endl;
}

void GLClearErr() 
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* func, const char* file, int line) 
{
    bool noErr = true;

    while (GLenum error = glGetError()) {

        std::cout << "[OpenGL Error] (0x0" << std::hex << error << ") at " << func << " in "
            << file << ":" << std::dec << line << std::endl;

        noErr = false;

    }

    return noErr;
}