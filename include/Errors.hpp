#pragma once

#include <cstdint>

enum class ERR : std::uint16_t
{
  // Global
  SUCCESS = 0x0000,
  FAIL = 0xffff,

  // File Stream
  FAILED_OPEN_FILE = 0x0010,
  FILE_DONT_EXISTS = 0x0011,

  // String
  EMPTY_STRING = 0x0020,

  // Shader
  SHADER_LINK_ERROR = 0x0030,
  FAILED_INSERT_VALUE = 0x0031,
  UNIFORM_NOT_FOUND = 0x0032,
  SHADER_COMPILE_ERROR = 0x0033,
  NOT_SUPPORTED_UNIFORM_TYPE = 0x0034,

  // Window
  FAILED_CREATE_WINDOW = 0x0040,
  FAILED_LOAD_GL_LOADER = 0x0041,

  // Texture
  FAILED_TO_LOAD_IMAGE = 0x0050,
  NOT_SUPPORTED_TEXTURE_TARGET = 0x0051,
};
