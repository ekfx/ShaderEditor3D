#pragma once

#include <glad/glad.h>

namespace GL
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// PROTOTYPE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <int gl_target = 0>
class VertexBufferObject
{
protected:
  GLuint ID;

public:
  VertexBufferObject() { glGenBuffers(1, &ID); }
  ~VertexBufferObject() { glDeleteBuffers(1, &ID); };
  void Bind(const int &target) { glBindBuffer(target, ID); }
  void Unbind(const int &target) { glBindBuffer(target, 0); }
  operator GLuint &() { return ID; }
};

typedef VertexBufferObject<0> BUFFER;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// GL_ARRAY_BUFFER
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <>
class VertexBufferObject<GL_ARRAY_BUFFER> : public VertexBufferObject<0>
{
private:
  int n_attrib = 0;
  int index = 0;

public:
  void Data(const int &target, const int &size, void *data, const int &draw, const int &total_n_of_attributes)
  {
    n_attrib = total_n_of_attributes;
    glBufferData(target, size, data, draw);
  }

  void Pointer(const int &index, const int &quantity, const int &type, const int &normalized, const int &stride, int &begin)
  {
    glVertexAttribPointer(index, quantity, type, normalized, stride, static_cast<void *>(&begin));
    glEnableVertexAttribArray(index);
  }

  // Default for floats and not normalized data:
  void Pointer(const int &quantity, const int &begin)
  {
    glVertexAttribPointer(index, quantity, GL_FLOAT, GL_FALSE, n_attrib * sizeof(float), (void *)(begin * sizeof(float)));
    glEnableVertexAttribArray(index);
    index++;
  }
};

typedef VertexBufferObject<GL_ARRAY_BUFFER> VBO;

} // namespace GL
