#pragma once

#include <GLFW/glfw3.h>

#include <string>

namespace odin {

    class Window {

    private:
        GLFWwindow* m_WindowID;
        int m_Width, m_Height;
        std::string m_Title;

    public:
        Window(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
        ~Window();

        void MakeContextCurrent();
        bool WindowShouldClose();
        bool WindowDoesNotExist();
        void SwapBuffers();

        GLFWwindow* GetId() { return m_WindowID; }

    };

    class IMGUIwindow {

    private:
        GLFWwindow* m_WindowID;
        int m_Width, m_Height;
        std::string m_Title;

    public:
        IMGUIwindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
        ~IMGUIwindow();

        void MakeContextCurrent();
        bool WindowShouldClose();
        bool WindowDoesNotExist();
        void SwapBuffers();

        void NewFrame();
        void Render();

    };

}