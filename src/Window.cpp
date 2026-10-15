#include "Window.hpp"

void WND::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
  glViewport(0, 0, width, height);
  WIDTH = width;
  HEIGHT = height;
  ASPECT_RATIO = width / height;
}

void WND::scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
  SCROLL_X_OFFSET = xoffset;
  SCROLL_Y_OFFSET = yoffset;
}

void WND::keyboard_callback(GLFWwindow *window, int key, int scancode,
                            int action, int mods)
{
  if (action == GLFW_PRESS || action == GLFW_REPEAT)
    KEYS.setBit(key, true);
  else
    KEYS.setBit(key, false);
}

void WND::mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
  if (action == GLFW_PRESS || action == GLFW_REPEAT)
    KEYS.setBit(button, true);
  else
    KEYS.setBit(button, false);
}

void WND::Create(const std::string &title, const int &width, const int &height)
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR_VERSION);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR_VERSION);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_COMPAT_FORWARD, GLFW_TRUE);
#endif

  PTR = glfwCreateWindow((int)width, (int)height, title.c_str(), nullptr,
                         nullptr);
  WIDTH = width;
  HEIGHT = height;
  ASPECT_RATIO = width / height;

  if (PTR == nullptr)
  {
    Log::err(ERR::FAILED_CREATE_WINDOW);
  }

  glfwSetKeyCallback(PTR, keyboard_callback);
  glfwSetMouseButtonCallback(PTR, mouse_button_callback);
  glfwSetFramebufferSizeCallback(PTR, framebuffer_size_callback);
  glfwSetScrollCallback(PTR, scroll_callback);

  glfwMakeContextCurrent(PTR);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    Log::err(ERR::FAILED_LOAD_GL_LOADER);
  }
}

void WND::Destroy() { glfwTerminate(); }

void WND::Routine()
{

  TIME.Run();
  FRAMETIME = TIME.Frametime();
  glfwGetCursorPos(PTR, &CURSOR_X, &CURSOR_Y);
  glfwPollEvents();
  glfwSwapBuffers(PTR);
}

void WND::Loop(const std::function<void()> &renderCallback)
{
  while (!glfwWindowShouldClose(PTR))
  {
    if (TIME.Tick(UPDATE_TITLE_INTERVAL))
    {
      glfwSetWindowTitle(
          PTR, std::string("FPS: " + std::to_string((int)TIME.FPS()) +
                           " | FT: " + std::to_string(TIME.Frametime()))
                   .c_str());
    }

    renderCallback();
    Routine();
  }
}

GLFWwindow *&WND::Get() { return PTR; }
