#pragma once

#include <SFML/System.hpp>

struct Observer
{
  sf::Vector3f pos;
  sf::Vector3f pointing;

  float FOVx;
  float FOVy;
};
