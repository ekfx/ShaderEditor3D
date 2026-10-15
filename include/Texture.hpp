#pragma once

#include <glad/glad.h>
#include "Errors.hpp"
#include "Log.hpp"

template <typename T>
concept IMG = requires(const T &obj) {
  { obj.width };
  { obj.height };
  { obj.channels };
  { obj.data };
};

namespace GL
{
class Texture
{
private:
  GLuint texture;
  int slot;
  int target;

  void Load(const int &texture_target, const int &texture_slot, int &width, int &height, const int &depth, void *data)
  {
    target = texture_target;
    slot = texture_slot;

    glActiveTexture(slot);
    glGenTextures(1, &texture);
    glBindTexture(target, texture);

    glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(target, GL_TEXTURE_WRAP_R, GL_REPEAT);
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    if (target == GL_TEXTURE_2D)
    {
      glTexImage2D(target, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(target);
    }
    else if (target == GL_TEXTURE_3D)
    {
      glTexImage3D(target, 0, GL_RGBA, width, height, depth, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(target);
    }
    else
    {
      Log::err(ERR::NOT_SUPPORTED_TEXTURE_TARGET);
    }
  }

public:
  void Bind()
  {
    glBindTexture(target, texture);
  }

  Texture(const int &texture_target, const int &texture_slot, int &width, int &height, const int &depth, void *data)
  {
    Load(texture_target, texture_slot, width, height, depth, data);
  }

  template <IMG T>
  Texture(const int &texture_target, const int &texture_slot, const int &depth, T &img)
  {
    Load(texture_target, texture_slot, img.width, img.height, depth, img.data);
  }

  ~Texture()
  {
    glDeleteTextures(1, &texture);
  }
};
} // namespace GL
