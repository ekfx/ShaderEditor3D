#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#include <string>

#include <functional>

typedef std::function<void()> DisplayFunc;

class Display
{
private:
  ImGuiContext *IMGUI_PTR = nullptr;
  std::function<void()> hud;

public:
  Display(GLFWwindow *wnd)
  {
    IMGUI_CHECKVERSION();
    IMGUI_PTR = ImGui::CreateContext();
    ImGui::SetCurrentContext(IMGUI_PTR);
    ImGuiIO &io = ImGui::GetIO();

    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(wnd, true);
    ImGui_ImplOpenGL3_Init();
  }

  ~Display()
  {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
  }

  void SetDisplay(const std::function<void()> custom_display, int width,
                  int height, int posx, int posy)
  {
    hud = custom_display;
    ImGui::SetNextWindowPos(ImVec2(posx, posy), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(width, height), ImGuiCond_Once);
  }

  void Run()
  {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    hud();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }
};
