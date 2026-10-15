#pragma once

#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Errors.hpp"

enum Movement
{
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT,
  UP,
  DOWN,

  FASTER,
  SLOWER,
  DEFAULT,

  FOV,
  SPEED,
  SENSIBILITY,
};

class Camera
{
private:
  glm::mat4 view, proj;
  glm::vec3 front, right, up, position;
  glm::vec3 dirvec_t;

  float yaw{}, pitch{};
  float dY{}, dX{};
  float iX{}, iY{};

  float fov;
  float speed;
  float sensi;
  float zNear, zFar;
  bool firstTime;

public:
  Camera(const glm::vec3 &target = glm::vec3(0.0f),
         const glm::vec3 &pos = glm::vec3(0.0f, 0.0f, -3.0f),
         const float &fov_ = 130.0f, const float &speed_ = 2.5f,
         const float &sensi_ = 180.0f, const float &znear = 0.1f,
         const float zfar = 100.0f);
  ~Camera();

  void InMove(const int &direction, const float &frametime);
  void InCursor(const float &xpos = 1, const float &ypos = 1, const float &frametime = 1);
  void InScroll(const float &xoffset = 1, const float &yoffset = 1);
  void Update(const float &aspect_ratio);

  void SetSpeed(const int &speed_mode);
  void Set(const int &which, const float &value);
  void SetCamera(const glm::vec3 &front_, const glm::vec3 &right_,
                 const glm::vec3 &up_, const glm::vec3 &position_);

  glm::mat4 &GetView();
  glm::mat4 &GetProjection();
  glm::vec3 &GetPosition();
  glm::vec3 &GetFront();
  glm::vec3 &GetRight();
  glm::vec3 &GetUp();
};
