#pragma once

#include "VertexArrayObject.hpp"
#include "VertexBufferObject.hpp"
#include "Texture.hpp"

namespace GL
{
void BeginStandard(GL::VAO &VAO, GL::VBO &VBO, const int &size, void *data, const int &n_attributes)
{
  VAO.Bind();
  VBO.Bind(GL_ARRAY_BUFFER);
  VBO.Data(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW, n_attributes);
}

void EndStandard(GL::VAO &VAO, GL::VBO &VBO)
{
  VAO.Unbind();
  VBO.Unbind(GL_ARRAY_BUFFER);
}
} // namespace GL
