#include "Game.h"

void Game::processEvents()
{
  sf::Event event;
  while(mWindow.pollEvent(event))
  {
    switch(event.type) {
      case sf::Event::KeyPressed:
        break;
      case sf::Event::KeyReleased:
        break;
      case sf::Event::Closed:
        mWindow.close();
        break;
      default:
        break;
    }
  }
}
void Game::update(sf::Time dT)
{}

void Game::projectOnPlane(sf::ConvexShape &shape, Triangle tmp)
{
  // float Asqrt = sqrt(tmp.A);
  float h = W / (2.f * tan(M_PI / 6.f));

  float kA = h / tmp.A.x;
  float kB = h / tmp.B.x;
  float kC = h / tmp.C.x;

  shape.setPoint(0, sf::Vector2f(tmp.A.y * kA + W/2, - tmp.A.z * kA + H/2));
  shape.setPoint(1, sf::Vector2f(tmp.B.y * kB + W/2, - tmp.B.z * kB + H/2));
  shape.setPoint(2, sf::Vector2f(tmp.C.y * kC + W/2, - tmp.C.z * kC + H/2));
}


void Game::render()
{
  rotate(triags, triagCount, 0.001);
  mWindow.clear();

  sf::Vector3f brightVec{ -1.f, 0, 0 };

  sf::ConvexShape triangle;
  triangle.setPointCount(3);

  Triangle tmp;
  for(uint32_t i=0; i<triagCount; i++) {
    transform(tmp, obs, triags[i]);
    sf::Vector3f N = getN(tmp);
    if(N.x < 0.2f and N.x > -0.2f)
      continue;
    projectOnPlane(triangle, tmp);
    triangle.setFillColor(sf::Color::Transparent);
    // triangle.setFillColor(
    //   sf::Color(250*(0.5f - 0.5f*dot(N, brightVec)), 15, 15));
    triangle.setOutlineThickness(1);
    triangle.setOutlineColor(sf::Color(255, 255, 255));
    mWindow.draw(triangle);
  }

  mWindow.display();
}

Game::Game()
  : TimePerFrame { sf::seconds(1.f/60.f) },
  mWindow(sf::VideoMode(W, H), "Heart 3d"),
  triags{ NULL },
  triagCount{ 0 },
  obs { {20, 0, -1}, {-1, 0, 0}, std::numbers::pi / 3.f }
{
  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;
  mWindow.create(sf::VideoMode(W, H), "Heart 3d", sf::Style::Default, settings);
  // mWindow.getSettings().antialiasingLevel = 8;
}

void Game::run()
{
  sf::Clock clock;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;
  while(mWindow.isOpen()) {
    processEvents();
    timeSinceLastUpdate += clock.restart();
    while(timeSinceLastUpdate > TimePerFrame) {
      timeSinceLastUpdate -= TimePerFrame;
      processEvents();
      update(TimePerFrame);
    }
    render();
  }
}

void Game::loadTriangles(std::string filename)
{
  std::ifstream file{ filename };
  std::string line;
  if(!file.is_open()) {
    std::cout << "failed to open file" << std::endl;
    return;
  }
  std::getline(file, line);
  triagCount = stoi(line);
  if(triags != NULL)
    delete [] triags;
  triags = new Triangle[triagCount];
  for(uint32_t i=0; i<triagCount; i++) {
    file >> triags[i].A.x;
    file >> triags[i].A.y;
    file >> triags[i].A.z;
    file >> triags[i].B.x;
    file >> triags[i].B.y;
    file >> triags[i].B.z;
    file >> triags[i].C.x;
    file >> triags[i].C.y;
    file >> triags[i].C.z;
  }

  file.close();

  rotate(triags, triagCount, M_PI/4.);
}
