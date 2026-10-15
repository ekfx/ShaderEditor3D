#pragma once

#include <glad/glad.h>
#include <glm/matrix.hpp>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <filesystem>
#include <string>
#include <fstream>
#include <sstream>
#include <type_traits>
#include <map>
#include "Errors.hpp"

template <typename T>
concept ptrcc = requires(const T &value) {
  { std::is_same_v<T, const char *> };
}; // const char pointer

template <typename T>
concept cc = requires(const T &value) {
  { std::is_same_v<T, const char> };
}; // pointer

template <typename T>
concept str = requires(const T &value) {
  { std::is_same_v<T, std::string> };
}; // std::string

template <typename T>
concept strv = requires(const T &value) {
  { std::is_same_v<T, std::string_view> };
}; // std::string_view

template <typename T>
concept syspath = requires(const T &value) {
  { std::is_same_v<T, std::filesystem::path> };
}; // std::filesystem::path

template <typename T>
concept PATH = requires {
  requires ptrcc<T>;
  requires str<T>;
  requires syspath<T>;
  requires cc<T>;
};

template <typename T>
concept SOURCE = requires {
  requires ptrcc<T>;
  requires str<T>;
  requires cc<T>;
  requires strv<T>;
};

// Manages a Shader instance
class Shader
{
private:
  std::map<std::string, GLint> Uniforms;
  GLuint sp; // Shader Program
  std::string infoLog;

public:
  Shader();
  ~Shader();

  ERR ReadFile(const std::filesystem::path &path,
               std::string &target) noexcept;

  // Creation and Delete
  template <typename T1, typename T2>
    requires PATH<T1> && PATH<T2>
  ERR CreateShaders(T1 &vert_path, T2 &frag_path) noexcept
  {
    infoLog = " ";

    std::filesystem::path vert = vert_path;
    std::filesystem::path frag = frag_path;

    vert.make_preferred();
    frag.make_preferred();

    infoLog += "<" + vert.string() + ", " + frag.string() + ">\n";

    std::string source;
    const char *c_str = "";

    //--------------------------------------------------------------------------

    GLuint vertShaderID = glCreateShader(GL_VERTEX_SHADER);

    auto result = ReadFile(vert, source);
    if (result != ERR::SUCCESS)
    {
      return result;
    }

    c_str = source.c_str();
    glShaderSource(vertShaderID, 1, &c_str, NULL);
    glCompileShader(vertShaderID);

    int success;
    glGetShaderiv(vertShaderID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      char infoLog_t[1024];
      glGetShaderInfoLog(vertShaderID, 1024, NULL, infoLog_t);
      infoLog +=
          "----------------------------------------------------\nVertex "
          "Shader:\n";

      for (int i = 0; i < 1024; i++)
      {
        infoLog += infoLog_t[i];
      }
      return ERR::SHADER_COMPILE_ERROR;
    }

    source = "";

    //--------------------------------------------------------------------------

    GLuint fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    result = ReadFile(frag, source);
    if (result != ERR::SUCCESS)
    {
      return result;
    }

    c_str = source.c_str(); // -> now is lvalue and have a address
    glShaderSource(fragShaderID, 1, &c_str, NULL);
    glCompileShader(fragShaderID);

    glGetShaderiv(fragShaderID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      char infoLog_t[1024];
      glGetShaderInfoLog(fragShaderID, 1024, NULL, infoLog_t);
      infoLog += "----------------------------------------------------"
                 "\nFragment Shader:\n";

      for (int i = 0; i < 1024; i++)
      {
        infoLog += infoLog_t[i];
      }
      return ERR::SHADER_COMPILE_ERROR;
    }

    //--------------------------------------------------------------------------

    sp = glCreateProgram();
    glAttachShader(sp, vertShaderID);
    glAttachShader(sp, fragShaderID);
    glLinkProgram(sp);

    glGetProgramiv(sp, GL_LINK_STATUS, &success);
    if (!success)
    {
      char infoLog_t[1024];
      glGetProgramInfoLog(sp, 1024, NULL, infoLog_t);
      for (int i = 0; i < 1024; i++)
      {
        infoLog += infoLog_t[i];
      }
      return ERR::SHADER_LINK_ERROR;
    }

    glDeleteShader(vertShaderID);
    glDeleteShader(fragShaderID);

    return ERR::SUCCESS;
  }

  template <typename T1, typename T2>
    requires SOURCE<T1> && SOURCE<T2>
  ERR CreateShaders(T1 &vert_source, T2 &frag_source,
                    const std::string &name) noexcept
  {
    infoLog = " ";
    infoLog += name + ": " + "<RAM Vertex Shader, RAM Fragment Shader>\n";

    std::string vsSource = std::string(vert_source);
    std::string fsSource = std::string(frag_source);
    const char *c_str_vs = vsSource.c_str();
    const char *c_str_fs = fsSource.c_str();

    //--------------------------------------------------------------------------

    GLuint vertShaderID = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertShaderID, 1, &c_str_vs, NULL);
    glCompileShader(vertShaderID);

    int success;
    glGetShaderiv(vertShaderID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      char infoLog_t[1024];
      glGetShaderInfoLog(vertShaderID, 1024, NULL, infoLog_t);
      infoLog +=
          "----------------------------------------------------\nVertex "
          "Shader:\n";

      for (int i = 0; i < 1024; i++)
      {
        infoLog += infoLog_t[i];
      }
      return ERR::SHADER_COMPILE_ERROR;
    }

    //--------------------------------------------------------------------------

    GLuint fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragShaderID, 1, &c_str_fs, NULL);
    glCompileShader(fragShaderID);

    glGetShaderiv(fragShaderID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      char infoLog_t[1024];
      glGetShaderInfoLog(fragShaderID, 1024, NULL, infoLog_t);
      infoLog += "----------------------------------------------------"
                 "\nFragment Shader:\n";

      for (int i = 0; i < 1024; i++)
      {
        infoLog += infoLog_t[i];
      }
      return ERR::SHADER_COMPILE_ERROR;
    }

    //--------------------------------------------------------------------------

    sp = glCreateProgram();
    glAttachShader(sp, vertShaderID);
    glAttachShader(sp, fragShaderID);
    glLinkProgram(sp);

    glGetProgramiv(sp, GL_LINK_STATUS, &success);
    if (!success)
    {
      char infoLog_t[1024];
      glGetProgramInfoLog(sp, 1024, NULL, infoLog_t);
      for (int i = 0; i < 1024; i++)
      {
        infoLog += infoLog_t[i];
      }
      return ERR::SHADER_LINK_ERROR;
    }

    glDeleteShader(vertShaderID);
    glDeleteShader(fragShaderID);

    return ERR::SUCCESS;
  }

  void DeleteShaders() const noexcept;

  // Utilitary
  void Use() const noexcept;

  // Set uniforms
  template <typename type_pers>
  ERR SetUniform(const std::string &key, const type_pers &value) noexcept
  {
    auto it = Uniforms.find(key); // searches for the key
    GLint location;

    if (it == Uniforms.end())
    { // didnt found
      location = glGetUniformLocation(
          sp, key.c_str()); // gets the location for the key
      if (Uniforms.insert({key, location}).second == false)
      { // inserts the location
        return ERR::FAILED_INSERT_VALUE;
      }
      if (location == -1)
      { // if went wrong in the unfirom, opengl returns -1
        return ERR::UNIFORM_NOT_FOUND;
      }
    }
    else
    { // found and put its second value in the var location
      location = it->second;
    }

    if constexpr (std::is_integral_v<type_pers>)
    {
      glUniform1i(location, value);
    }
    else if constexpr (std::is_floating_point_v<type_pers>)
    {
      glUniform1f(location, value);
    }
    else if constexpr (std::is_same_v<type_pers, glm::vec4>)
    {
      glUniform4fv(location, 1, glm::value_ptr(value));
    }
    else if constexpr (std::is_same_v<type_pers, glm::vec3>)
    {
      glUniform3fv(location, 1, glm::value_ptr(value));
    }
    else if constexpr (std::is_same_v<type_pers, glm::vec2>)
    {
      glUniform2fv(location, 1, glm::value_ptr(value));
    }
    else if constexpr (std::is_same_v<type_pers, glm::mat4>)
    {
      glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
    }
    else if constexpr (std::is_same_v<type_pers, glm::mat3>)
    {
      glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
    }
    else if constexpr (std::is_same_v<type_pers, glm::mat2>)
    {
      glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(value));
    }

    return ERR::SUCCESS;
  }

  // Set uniforms, but this times is recepts the location as parameter,
  // voiding using find function every frame
  //  to get the location, use the Get function, that will return a location
  //  and you can save in your main routine.
  template <typename type_pers>
  ERR SetUniform(GLint &location, const type_pers &value) noexcept
  {
    if (location == -1)
    {
      return ERR::UNIFORM_NOT_FOUND;
    }

    if constexpr (std::is_integral_v<type_pers>)
    {
      glUniform1i(location, value);
    }
    else if constexpr (std::is_floating_point_v<type_pers>)
    {
      glUniform1f(location, value);
    }
    else if constexpr (std::is_same_v<type_pers, glm::vec4>)
    {
      glUniform4fv(location, 1, glm::value_ptr(value));
    }
    else if constexpr (std::is_same_v<type_pers, glm::vec3>)
    {
      glUniform3fv(location, 1, glm::value_ptr(value));
    }
    else if constexpr (std::is_same_v<type_pers, glm::vec2>)
    {
      glUniform2fv(location, 1, glm::value_ptr(value));
    }
    else if constexpr (std::is_same_v<type_pers, glm::mat4>)
    {
      glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
    }
    else if constexpr (std::is_same_v<type_pers, glm::mat3>)
    {
      glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
    }
    else if constexpr (std::is_same_v<type_pers, glm::mat2>)
    {
      glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(value));
    }
    else
    {
      return ERR::NOT_SUPPORTED_UNIFORM_TYPE;
    }

    return ERR::SUCCESS;
  }

  ERR GetLocation(const std::string &name, GLint &target) const noexcept
  {
    if (name.empty())
    {
      return ERR::EMPTY_STRING;
    }
    else
    {
      GLint target_t = glGetUniformLocation(sp, name.c_str());
      if (target_t == -1)
      {
        return ERR::UNIFORM_NOT_FOUND;
      }
      else
      {
        target = target_t;
        return ERR::SUCCESS;
      }
    }
  }

  // Getters
  std::string &GetInfoLog() noexcept;
  GLuint GetProgram() const noexcept;
};
