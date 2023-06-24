#include "game.h"
#include <ctime>
int main() {
  // Initalize random seed
  srand(static_cast<unsigned>(time(0)));
  Game game{800, 600};

  while (game.isRunning()) {
    game.update();
    game.render();
  }

  return 0;
}
