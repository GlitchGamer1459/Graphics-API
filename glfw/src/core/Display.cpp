#include <GLFW/glfw3.h>

#include <iostream>

#include "Display.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

Window::Window(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share) :
    m_Width(width), m_Height(height), m_Title(title)
{
    m_WindowID = glfwCreateWindow(width, height, title, monitor, share);
}

Window::~Window() { glfwTerminate(); }

void Window::MakeContextCurrent() { glfwMakeContextCurrent(m_WindowID); }

bool Window::WindowShouldClose() { return glfwWindowShouldClose(m_WindowID); }

bool Window::WindowDoesNotExist() { return !m_WindowID; }

void Window::SwapBuffers() { glfwSwapBuffers(m_WindowID); }



IMGUIwindow::IMGUIwindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share) :
    m_Width(width), m_Height(height), m_Title(title)
{
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(m_WindowID, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::StyleColorsDark();

    m_WindowID = glfwCreateWindow(width, height, title, monitor, share);
}

IMGUIwindow::~IMGUIwindow() 
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
}

void IMGUIwindow::MakeContextCurrent() { glfwMakeContextCurrent(m_WindowID); }

bool IMGUIwindow::WindowShouldClose() { return glfwWindowShouldClose(m_WindowID); }

bool IMGUIwindow::WindowDoesNotExist() { return !m_WindowID; }

void IMGUIwindow::SwapBuffers() { glfwSwapBuffers(m_WindowID); }

void IMGUIwindow::NewFrame() 
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void IMGUIwindow::Render() 
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}