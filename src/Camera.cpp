#include "Camera.hpp"

Camera::Camera(const glm::vec3 &target, const glm::vec3 &pos, const float &fov_, const float &speed_, const float &sensi_, const float &znear, const float zfar)
{
  fov = (fov_ < 130.0f && fov_ > 30.0f) ? fov_ : 90.0f;
  speed = speed_;
  sensi = sensi_;
  firstTime = true;
  zNear = znear;
  zFar = zfar;

  position = pos;
  glm::vec3 direction_t = glm::normalize(position - target);
  glm::vec3 up_t = glm::vec3(0.0f, 1.0f, 0.0f);

  // glm::cross cria um vetor perpendicular positiva a dois vetores
  // glm::dot mede de 0 a 1 o quao paralelo está dois vetores;
  right = glm::normalize(glm::cross(up_t, direction_t));
  up = glm::normalize(glm::cross(direction_t, right));
  front = glm::vec3(0.0f, 0.0f, -1.0f);
}

Camera::~Camera()
{
}

void Camera::InMove(const int &direction, const float &frametime)
{

  if (direction == FORWARD)
  {
    position += front * speed * frametime;
  }
  else if (direction == BACKWARD)
  {
    position -= front * speed * frametime;
  }

  else if (direction == RIGHT)
  {
    position += glm::normalize(glm::cross(front, up)) * speed * frametime;
  }
  else if (direction == LEFT)
  {
    position -= glm::normalize(glm::cross(front, up)) * speed * frametime;
  }

  else if (direction == UP)
  {
    position += up * speed * frametime;
  }
  else if (direction == DOWN)
  {
    position -= up * speed * frametime;
  }
}

void Camera::InCursor(const float &xpos, const float &ypos, const float &frametime)
{
  if (firstTime)
  {
    iX = xpos;
    iY = ypos;
    firstTime = false;
  }

  dX = (xpos - iX) * sensi * frametime;
  dY = (iY - ypos) * sensi * frametime;

  yaw += dX;
  pitch += dY;

  iX = xpos;
  iY = ypos;

  if (pitch > 89.0f)
  {
    pitch = 89.0f;
  }
  else if (pitch < -89.0f)
  {
    pitch = -89.0f;
  }

  dirvec_t.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  dirvec_t.y = sin(glm::radians(pitch));
  dirvec_t.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  front = glm::normalize(dirvec_t);
}

void Camera::InScroll(const float &xoffset, const float &yoffset)
{
  fov += yoffset;
  if (fov > 130.0f)
  {
    fov = 130.0f;
  }

  if (fov < 30.0f)
  {
    fov = 30.0f;
  }
}

void Camera::SetSpeed(const int &speed_mode)
{
  if (speed_mode == FASTER)
    speed = 15.0f;
  else if (speed_mode == SLOWER)
    speed = 1.25f;
  else if (speed_mode == DEFAULT)
    speed = 2.5f;
}

void Camera::Set(const int &which, const float &value)
{
  if (which == FOV)
    fov = value;

  if (which == SPEED)
    speed = value;

  if (which == SENSIBILITY)
    sensi = value;
}

void Camera::SetCamera(const glm::vec3 &front_, const glm::vec3 &right_, const glm::vec3 &up_, const glm::vec3 &position_)
{
  front = front_;
  right = right_;
  up = up_;
  position = position_;
}

glm::mat4 &Camera::GetView()
{
  return view;
}

glm::mat4 &Camera::GetProjection()
{
  return proj;
}

glm::vec3 &Camera::GetPosition()
{
  return position;
}

glm::vec3 &Camera::GetFront()
{
  return front;
}

glm::vec3 &Camera::GetRight()
{
  return right;
}

glm::vec3 &Camera::GetUp()
{
  return up;
}

void Camera::Update(const float &aspect_ratio)
{
  proj = glm::perspective(glm::radians(fov), aspect_ratio, 0.1f, 100.0f);
  view = glm::lookAt(position, position + front, up);
}
