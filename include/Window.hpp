#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <functional>

#include "Types.hpp"
#include "Errors.hpp"
#include "Log.hpp"
#include "Clock.hpp"

class WND
{
  static constexpr int KEYBOARD_SIZE = 512;
  static constexpr int OPENGL_MAJOR_VERSION = 4;
  static constexpr int OPENGL_MINOR_VERSION = 3;

private:
  inline static GLFWwindow *PTR;
  inline static float UPDATE_TITLE_INTERVAL = 1.5F;

  // Callbacks
  static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
  static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
  static void keyboard_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
  static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);

public:
  inline static float WIDTH;
  inline static float HEIGHT;
  inline static float ASPECT_RATIO;
  inline static double SCROLL_X_OFFSET;
  inline static double SCROLL_Y_OFFSET;
  inline static double CURSOR_X;
  inline static double CURSOR_Y;
  inline static Bit<KEYBOARD_SIZE> KEYS;
  inline static double FRAMETIME;
  inline static Clock TIME;

  static void Create(const std::string &title, const int &width, const int &height);
  static void Destroy();

  static void Routine();
  static void Loop(const std::function<void()> &renderCallback);

  static GLFWwindow *&Get();
};
