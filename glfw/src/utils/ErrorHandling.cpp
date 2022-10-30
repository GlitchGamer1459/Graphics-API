#include "ErrorHandling.h"

int OdinGlfwInit()
{
    if (!glfwInit())
        return 0;

    glfwSetErrorCallback(GlfwErrorCallback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

int OdinGlewInit()
{
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return 0;
    }

    glfwSwapInterval(1);

    std::cout << "using OpenGL version " << glGetString(GL_VERSION) << std::endl;
    std::cout << "using GLFW version " << glfwGetVersionString() << std::endl;
    std::cout << "using GLEW version " << glewGetString(GLEW_VERSION) << std::endl;
}

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