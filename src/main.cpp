#include <glm/common.hpp>
#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <meta>
#include <vector>
#include <random>

// #include "Image.hpp"
#include "OpenGLWrapper.hpp"
#include "Window.hpp"
#include "Shader.hpp"
#include "Types.hpp"
#include "Camera.hpp"
#include "GLFW/glfw3.h"
#include "Display.hpp"
#include "Log.hpp"
#include "Primitives.hpp"

Camera Cam;
Shader cubeShader;

void Input(const float &FRAMETIME) noexcept;
std::string Rename(const std::string &def, const std::string &sufix);

int main()
{
  WND::Create("WND", 800.0F, 600.0F);
  glfwSwapInterval(0);

  ///////////////////////////////////////////////////////////////////////
  /// Buffers

  GL::VAO VAO;
  GL::VBO VBO;
  GL::BeginStandard(VAO, VBO, sizeof(CUBE), CUBE, 6);
  VBO.Pointer(3, 0);
  VBO.Pointer(3, 3);
  GL::EndStandard(VAO, VBO);

  ///////////////////////////////////////////////////////////////////////
  /// Shaders
  constexpr int SHADER_BUFFER_SIZE = 16384;
  constexpr int SHADER_PATH_BUFFER_SIZE = 1024;
  std::string VERTEX_SHADER_PATH = "shaders/vsActor.glsl";
  std::string FRAGMENT_SHADER_PATH = "shaders/fsActor.glsl";
  std::string VertexSource;
  std::string FragmentSource;

  Shader lightShader;
  Log::errf(lightShader.CreateShaders("shaders/vsLight.glsl", "shaders/fsLight.glsl"), lightShader.GetInfoLog());

  Log::errf(cubeShader.CreateShaders(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH), cubeShader.GetInfoLog());

  ///////////////////////////////////////////////////////////////////////
  /// Math Data
  struct MODEL
  {
    glm::vec4 rotation;
    glm::vec3 color, position, scale;
  };

  // some buffers to imgui
  MODEL nMember;
  float position[3] = {0.0f, 0.0f, 0.0f};
  float color[3] = {0.9f, 0.8f, 0.9f};
  float rotation[4] = {0.0f, 0.0f, 0.0f, 0.0f};
  float scale[3] = {1.0f, 1.0f, 1.0f};
  bool axis[3] = {1, 0, 0};

  // Data to render,
  std::vector<MODEL> Cubes;
  glm::vec3 bgColor = glm::vec3(0.3f);
  glm::mat4 model;

  glm::vec3 lightPos = glm::vec3(5.0f, 2.0f, 0.0f);
  glm::vec3 lightColor = glm::vec3(1.0f);
  float lightSize = 0.25f;

  ///////////////////////////////////////////////////////////////////////
  /// Display
  bool lightOnHead = false;
  bool saveCommand = false;

  cubeShader.ReadFile(VERTEX_SHADER_PATH, VertexSource);
  cubeShader.ReadFile(FRAGMENT_SHADER_PATH, FragmentSource);
  VertexSource.reserve(SHADER_BUFFER_SIZE);
  FragmentSource.reserve(SHADER_BUFFER_SIZE);
  VERTEX_SHADER_PATH.reserve(SHADER_PATH_BUFFER_SIZE);
  FRAGMENT_SHADER_PATH.reserve(SHADER_PATH_BUFFER_SIZE);

  Display Editor(WND::Get());
  Editor.SetDisplay([&]() {
    ImGui::Begin("Hot-Reload", NULL, 0);

    ImGui::TextWrapped(
      "Welcome to my shader hot-reloader, it is not sofisticated but"
      "I hope this could help you or just serve as a product to my portfolio.\n"
    );
    ImGui::NewLine();

    if (ImGui::CollapsingHeader("Read Me")) {
       ImGui::TextWrapped(
         "To start, I need to warn some issues in the current version of the program:"
         "1. I tried to create a path input to read a specific shader but I couldn't do it yet.\n"
         "2. The camera is weird because the mouse position changes so much in comparasion with the last position.\n"
         "3. Inside the program the architecture is not beautiful, but at least it works. I will change it.\n"
         "4. There aren't many uniforms and there is no texture.\n"
         "5. Remember, this application was not made to compete with the bigs, is just a application I made to my own learning,"
         "actually this exists because I was needing a better environment to study Phong Shaders.\n"
         "\n"
         "That's all, use the below sections to learn more.\n"
       );
      ImGui::NewLine();
    }

    if (ImGui::CollapsingHeader("Help")) {
      ImGui::TextWrapped(
        "To get started, this is a very simple application:\n"
        "1. Starting from the below section. This is the Editor, you can edit the shaders and apply with the button below,"
        "use the save to save in the current shader, or use the Export New to create a new pair of shaders renamed. I'm trying to"
        "put a name input to load and export shaders.\n"
        "2. The Environment Section is where you will change if the camera must be in your head camera or rotating in the center,"
        "and you can change the background color as you want.\n"
        "3. In the last section, World, you can create cube and pop the last you created. You have sliders to position, scale, degrees etc."
        "It don't have undo or redo for the cubes even a export structure.\n"
      );
      ImGui::NewLine();
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if (ImGui::CollapsingHeader("Editor")) {
      ImGui::InputTextMultiline("Vertex", &VertexSource[0], SHADER_BUFFER_SIZE, ImVec2(400, 250));
      ImGui::InputTextMultiline("Fragment", &FragmentSource[0], SHADER_BUFFER_SIZE, ImVec2(400, 250));

      if (ImGui::Button("Apply Shaders")) {
        cubeShader.DeleteShaders();
        cubeShader.CreateShaders(VertexSource, FragmentSource, "Cube");
        Log::errm(cubeShader.GetInfoLog());
      }

      if (ImGui::Button("Save") || saveCommand) { 
        { std::ofstream file(VERTEX_SHADER_PATH);                         file << VertexSource; }
        { std::ofstream file(FRAGMENT_SHADER_PATH);                       file << FragmentSource; }                  
      }
    
      if (ImGui::Button("Export New")) {
        { std::ofstream file(Rename(VERTEX_SHADER_PATH, ".glsl"));        file << VertexSource; }
        { std::ofstream file(Rename(FRAGMENT_SHADER_PATH, ".glsl"));      file << FragmentSource; }
      }
      ImGui::NewLine();
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if (ImGui::CollapsingHeader("Environment")) {
      float fbgColor[3] = { bgColor.r, bgColor.g, bgColor.b };
      ImGui::ColorEdit3("Background Color", fbgColor);
      bgColor = glm::vec3(fbgColor[0],fbgColor[1],fbgColor[2]);

      if (ImGui::Button(std::string("Light On Head (" + std::to_string(lightOnHead) + ")").c_str())) {
        lightOnHead = !lightOnHead;
      }
      ImGui::NewLine();
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if (ImGui::CollapsingHeader("World")) {
      ImGui::SliderFloat3("Position", position, -100.0f, 100.0f);
      nMember.position = glm::vec3(position[0],position[1],position[2]);
      
      ImGui::ColorEdit3("Color", color);
      nMember.color = glm::vec3(color[0],color[1],color[2]);
      
      ImGui::SliderFloat3("Scale", scale, -100.0f, 100.0f);
      nMember.scale = glm::vec3(scale[0],scale[1],scale[2]);
      
      ImGui::TextWrapped("Choose which axis to rotate the model:");
      ImGui::Checkbox("X", &axis[0]); rotation[0] = (float)axis[0];
      ImGui::Checkbox("Y", &axis[1]); rotation[1] = (float)axis[1];
      ImGui::Checkbox("Z", &axis[2]); rotation[2] = (float)axis[2];
      ImGui::SliderFloat("Rotation", &rotation[3], 0.0f, 360.0f);
      nMember.rotation = glm::vec4(rotation[0],rotation[1],rotation[2],rotation[3]);

      if (ImGui::Button("Add")) {
        Cubes.push_back(nMember);
      }

      if (ImGui::Button("Pop Last")) {
        if (Cubes.size() > 1) 
          Cubes.pop_back();
      }

      if (ImGui::Button("Clear All")) {
        Cubes.clear();
      }

      if (ImGui::Button("Add (10) Random")) {
        std::random_device rd{};
        std::mt19937 mt{rd()};
        std::uniform_real_distribution<float> rnd(-50.0f, 50.0f);
        std::uniform_real_distribution<float> col(0.2f, 1.0f);
        for (int i = 0; i < 10; i++) {
          nMember.rotation = glm::vec4(rnd(mt), rnd(mt), rnd(mt), rnd(mt));
          nMember.position = glm::vec3(rnd(mt), rnd(mt), rnd(mt));
          nMember.color = glm::vec3(col(mt), col(mt), col(mt));
          nMember.scale = glm::vec3(rnd(mt), rnd(mt), rnd(mt));
          Cubes.push_back(nMember);
        }
      }
      ImGui::NewLine();
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ImGui::End(); 
  }, 200, 200, 0, 0);

  ///////////////////////////////////////////////////////////////////////
  /// Render Loop

  glEnable(GL_DEPTH_TEST);
  WND::Loop([&]() {
    glClearColor(bgColor.r, bgColor.g, bgColor.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Cam.Update(WND::ASPECT_RATIO);
    Input(WND::FRAMETIME);
    VAO.Bind();

    lightShader.Use();
    model = glm::mat4(1.0f);
    if (lightOnHead)
      lightPos = glm::vec3(Cam.GetPosition());
    else
      lightPos = glm::vec3(sin(glfwGetTime()), cos(glfwGetTime() * 0.618f), cos(glfwGetTime()));

    model = glm::translate(model, lightPos);
    model = glm::scale(model, glm::vec3(lightSize));
    lightShader.SetUniform("lightColor", lightColor);
    lightShader.SetUniform("model", model);
    lightShader.SetUniform("projection", Cam.GetProjection());
    lightShader.SetUniform("view", Cam.GetView());
    if (!lightOnHead)
      glDrawArrays(GL_TRIANGLES, 0, 36);

    ///////////////////////////////////////////////////////////////////////////////////////
    /// Cube
    ///////////////////////////////////////////////////////////////////////////////////////

    cubeShader.Use();
    cubeShader.SetUniform("lightPos", lightPos);
    cubeShader.SetUniform("lightColor", lightColor);
    cubeShader.SetUniform("viewPos", Cam.GetPosition());

    cubeShader.SetUniform("projection", Cam.GetProjection());
    cubeShader.SetUniform("view", Cam.GetView());

    for (auto &member : Cubes)
    {
      cubeShader.SetUniform("time", glfwGetTime());
      cubeShader.SetUniform("resolution", glm::vec2(WND::WIDTH, WND::HEIGHT));

      model = glm::mat4(1.0f);
      model = glm::translate(model, member.position);
      model = glm::rotate(model, glm::radians(member.rotation.w), glm::vec3(member.rotation.x, member.rotation.y, member.rotation.z));
      model = glm::scale(model, member.scale);
      cubeShader.SetUniform("cubeColor", member.color);
      cubeShader.SetUniform("model", model);
      glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    Editor.Run(); 
  });

  ///////////////////////////////////////////////////////////////////////
  /// Release
  WND::Destroy();

  return 0;
}

void Input(const float &FRAMETIME) noexcept
{
  if (WND::KEYS.isTrue(GLFW_MOUSE_BUTTON_RIGHT))
  {
    glfwSetInputMode(WND::Get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    Cam.InCursor(WND::CURSOR_X, WND::CURSOR_Y, FRAMETIME);

    if (WND::KEYS.isTrue(GLFW_KEY_W))
      Cam.InMove(FORWARD, FRAMETIME);
    if (WND::KEYS.isTrue(GLFW_KEY_A))
      Cam.InMove(LEFT, FRAMETIME);
    if (WND::KEYS.isTrue(GLFW_KEY_S))
      Cam.InMove(BACKWARD, FRAMETIME);
    if (WND::KEYS.isTrue(GLFW_KEY_D))
      Cam.InMove(RIGHT, FRAMETIME);
    if (WND::KEYS.isTrue(GLFW_KEY_LEFT_SHIFT))
      Cam.InMove(UP, FRAMETIME);
    if (WND::KEYS.isTrue(GLFW_KEY_LEFT_CONTROL))
      Cam.InMove(DOWN, FRAMETIME);

    if (WND::KEYS.isTrue(GLFW_KEY_SPACE)) 
      Cam.SetSpeed(FASTER);
    else 
      Cam.SetSpeed(DEFAULT);
  }
  else
  {
    glfwSetInputMode(WND::Get(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
  }
}

std::string Rename(const std::string &def, const std::string &sufix)
{
  int i = 0;
  std::string outName = def;
  do
  {
    outName = def;
    outName.erase((outName.length() - 1) - (sufix.length() - 2), sufix.length());
    outName += std::to_string(i);
    outName += sufix;
    i++;
  } while (std::filesystem::exists(std::filesystem::path(outName)));
  return outName;
}
