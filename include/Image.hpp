#pragma once

#define STB_IMAGE_IMPLEMENTATION
#include <stbi/stb_image.h>
#include <filesystem>
#include <string>
#include "Errors.hpp"
#include "Log.hpp"

namespace IMAGE
{
struct IMG
{
  int width;
  int height;
  int channels;
  unsigned char *data;
};

ERR Create(IMG &target, const std::string &location)
{
  std::filesystem::path path = location;
  path.make_preferred();
  target.data = stbi_load(path.string().c_str(), &target.width, &target.height, &target.channels, 4);

  if (!target.data)
  {
    return ERR::FAILED_TO_LOAD_IMAGE;
  }
  else
  {
    return ERR::SUCCESS;
  }
}

void Destroy(IMG &target)
{
  if (target.data)
  {
    stbi_image_free(target.data);
  }
  else
  {
  }
}
}; // namespace IMAGE
