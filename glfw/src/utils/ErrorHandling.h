#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <csignal>

#define ASSERT(x) if (!x) {\
        std::cout << "ASSERT triggered at " << __FILE__ << ": " << __LINE__ << std::endl;\
        raise(SIGABRT);\
    }

#define GLCall(x) GLClearErr();\
        x;\
        ASSERT(GLLogCall(#x, __FILE__, __LINE__))

int OdinGlfwInit();
int OdinGlewInit();

void GlfwErrorCallback(int code, const char* errmsg);
void GLClearErr();
bool GLLogCall(const char* func, const char* file, int line);