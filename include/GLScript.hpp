#pragma once

#include <iostream>
#include <string>
#include <meta>
#include <glm/common.hpp>
#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <random>

#include "Log.hpp"

struct Geometric
{
  glm::mat4 model;
  glm::vec4 spin;
  glm::vec3 color;
  glm::vec3 velocity;  

  Geometric(glm::vec3 pos = glm::vec3(0.0f), 
            glm::vec4 rot = glm::vec4(1.0f), 
            glm::vec3 scale = glm::vec3(1.0f),
            glm::vec4 spin_ = glm::vec4(1.0f), 
            glm::vec3 vel = glm::vec3(0.0f), 
            glm::vec3 col = glm::vec3(1.0f))
  {
    std::cout << rot.x << " - " << rot.y << " - " << rot.z << " - " << rot.w << "\n";
    std::cout << scale.x << " - " << scale.y << " - " << scale.z << "\n";
    model = glm::mat4(1.0f);
    model = glm::translate(model, pos);
    model = glm::rotate(model, glm::radians(rot.w), glm::vec3(rot.x, rot.y, rot.z));
    model = glm::scale(model, scale);

    spin = spin_;
    color = col;
    velocity = vel;
  }
};

class GLScriptParser
{
private:
  std::string GLScript;
  int numbers_of;

public:
  GLScriptParser();
  std::string &Get();
  void Interpret(std::vector<Geometric>& target);
};

GLScriptParser::GLScriptParser()
{
  numbers_of = 0;
  std::string buf;
  for (int i = 0; i < 8191; i++)
  {
    buf += " ";
  }
  buf += "\0";
  GLScript = buf;
}

std::string &GLScriptParser::Get()
{
  return GLScript;
}

void GLScriptParser::Interpret(std::vector<Geometric>& target)
{
  /*
   * Lines must end with ;
   * You can create variables with: Geometric
   * Only and every Geometric will be shown
   * The instantiation follows:
   * Geometric | myCube | <.>;
   */

  std::string raw = GLScript;
  std::cout << raw << std::endl;

  for (int i = raw.length() - 1; i >= 0; i--)
  {
    if (raw[i] == ';')
      raw[i] = '\n';

    if (raw[i] == ' ')
    {
      raw.erase(i, 1);
    }
  }

  std::string buffer = "";
  std::string cmd = "";
  std::string value = "";
  for (int i = 0; i < raw.length(); i++)
  {
    if (raw[i] != '\n')
    {
      buffer += raw[i];
    }
    else
    {
      buffer += "\n";
      int chmod = 0;
      for (int j = 0; j < buffer.length(); j++)
      {
        if (buffer[j] == '|')
        {
          chmod++;
        }
        else
        {

          if (chmod == 0)
          {
            cmd += buffer[j];
          }
          else if (chmod == 1)
          {
            value += buffer[j];
          }
        }
      }
      buffer = "";
      std::cout << cmd << std::endl;
      std::cout << value << std::endl;

      std::random_device rd;  
      std::mt19937 gen(rd()); 
      std::uniform_real_distribution<float> sort(-5.0f, 5.0f);
      std::uniform_real_distribution<float> larger(1.0f, 360.0f);
      std::uniform_real_distribution<float> color(0.0f, 1.0f);

      if (cmd ==  "Cube") {
        for (int j = 1; j < value.length()-2; j++) {
          if (value[j] == '.') {
            
            target.push_back({glm::vec3(sort(gen), sort(gen), sort(gen)),
                              glm::vec4(sort(gen),sort(gen), sort(gen), larger(gen)),
                              glm::vec3(1.0f), 
                              glm::vec4(sort(gen), sort(gen),sort(gen), larger(gen)), 
                              glm::vec3(sort(gen), sort(gen),sort(gen)), 
                              glm::vec3(color(gen), color(gen), color(gen))});
          } else {
            /*
            int k = i;
            int index = 0;
            glm::vec4 vec = glm::vec4(1.0f);
            std::string colorBuffer = "";
            while (k != value.length()-2) {
              if (value[k] != ',') {
                colorBuffer += value[k];
              } else {
                auto v = std::stof(colorBuffer);
                vec[index] = v;
                colorBuffer = "";
                index++;
              }
              k++;
            }
            */
          }
        }
      } else {
        Log::errm("Unrecognized Command.");
      }
    }
  }

  std::cout << raw;
}
