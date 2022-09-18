#pragma once

#include <numbers>
#include <iostream>
#include <fstream>
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Observer.h"
#include "Triangle.h"
#include "Utils.h"

class Game
{
private:
  const uint32_t W = 800;
  const uint32_t H = 600;

  sf::Time TimePerFrame;

  sf::RenderWindow mWindow;

  Triangle *triags;
  unsigned int triagCount;
  Observer obs;

  void projectOnPlane(sf::ConvexShape &, Triangle);

  void processEvents();
  void update(sf::Time);
  void render();
public:
  Game();
  void run();
  void loadTriangles(std::string filename);
};
