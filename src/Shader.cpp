#include "Shader.hpp"

Shader::Shader() {}
Shader::~Shader() { DeleteShaders(); }

ERR Shader::ReadFile(const std::filesystem::path &path,
                     std::string &target) noexcept
{
  std::ifstream file;

  if (!std::filesystem::exists(path))
  {
    return ERR::FILE_DONT_EXISTS;
  }

  file.open(path);
  if (file.is_open())
  {
    std::stringstream target_t{};
    target_t << file.rdbuf();
    target = target_t.str();

    if (target.empty())
    {
      return ERR::EMPTY_STRING;
    }
    else
    {
      return ERR::SUCCESS;
    }
  }
  else
  {
    return ERR::FAILED_OPEN_FILE;
  }
  file.close();
}

void Shader::DeleteShaders() const noexcept
{
  if (sp != 0)
  {
    glDeleteProgram(sp);
  }
}

// Utilitary
void Shader::Use() const noexcept { glUseProgram(sp); }

// Getters
std::string &Shader::GetInfoLog() noexcept
{
  return infoLog;
}

GLuint Shader::GetProgram() const noexcept { return sp; }
