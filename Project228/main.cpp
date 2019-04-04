#include <iostream>
#include "main_headers.h"
#include "player.h"

using namespace std;
using namespace sf;

int main() {
  int width = 720, height = 480;
  View view;
  RenderWindow main_window(VideoMode(static_cast<unsigned int>(width),
                                     static_cast<unsigned int>(height)), "Project228");
  view.reset(FloatRect(0, 0, width, height));

  Player player("hulk.png", 100, 100, 100, 100, 100, 100, 100);

  sf::Clock timer_for_animation_;
  double cur_frame = 0;

  while (main_window.isOpen()) {
    double time = timer_for_animation_.getElapsedTime().asMicroseconds();
    timer_for_animation_.restart();

    Event event;
    while (main_window.pollEvent(event)) {
      if (event.type == sf::Event::Closed ||
          Keyboard::isKeyPressed(Keyboard::Escape)) {
        main_window.close();
      }

      if (player.IsAlive()) {
        if (Keyboard::isKeyPressed(Keyboard::W)) {
          player.SetDirection(Direction::N);
        } else if (Keyboard::isKeyPressed(Keyboard::A)) {
          player.SetDirection(Direction::W);
        } else if (Keyboard::isKeyPressed(Keyboard::S)) {
          player.SetDirection(Direction::S);
        } else if (Keyboard::isKeyPressed(Keyboard::D)) {
          player.SetDirection(Direction::E);
        } else {
          //player.SetDirection(Direction::STAY);
        }
      }
      player.Move(time / 1000);
    }

    main_window.setView(view);

    main_window.clear(Color(255, 255, 255));

    main_window.draw(*player.GetSprite());
    main_window.display();
  }

  return 0;
}
