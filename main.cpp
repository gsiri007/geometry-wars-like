#include <cstdlib>
#include "Game.hpp"

int main ()
{
  Game game("config.txt");
  game.run();

  return EXIT_SUCCESS;
}
