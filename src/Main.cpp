#include "Game.h"

using namespace std;

int main()
{
  Game game;
  game.loadTriangles("heart.txt");
  game.run();
}
