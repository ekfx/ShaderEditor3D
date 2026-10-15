#pragma once

#include <glad/glad.h>

namespace GL
{
class VertexArrayObject
{
private:
  GLuint ID;

public:
  VertexArrayObject() { glGenVertexArrays(1, &ID); }
  ~VertexArrayObject() { glDeleteVertexArrays(1, &ID); }

  void Bind() { glBindVertexArray(ID); }
  void Unbind() { glBindVertexArray(0); }

  operator GLuint() const noexcept { return ID; }
};

typedef VertexArrayObject VAO;
} // namespace GL
