#include <iostream>
#include <vector>
#include <fstream>
#include "main_headers.h"
#include "player.h"
#include "functions.h"

using namespace std;
using namespace sf;

int main() {
  vector<vector<int>> map_tiles(MAP_HEIGHT, vector<int>(MAP_WIDTH));
  vector<TileInfo> tiles(TILES_CNT);
  GetAllInformation(map_tiles, tiles);

  Image map_image;
  map_image.loadFromFile("img/map.png");
  Texture map_texture;
  map_texture.loadFromImage(map_image);
  Sprite map_sprite;
  map_sprite.setTexture(map_texture);

  int width = 2176, height = 1536;
  View view;
  RenderWindow main_window(VideoMode(static_cast<unsigned int>(width),
                                     static_cast<unsigned int>(height)), "Project228");
  view.reset(FloatRect(0, 0, width, height));

  Player player("hulk.png", 1500, 1000, 100, 100, 100);

  Clock timer_for_animation_;

  while (main_window.isOpen()) {
    double time = timer_for_animation_.getElapsedTime().asMicroseconds();
    timer_for_animation_.restart();

    Event event;
    while (main_window.pollEvent(event)) {
      if (event.type == Event::Closed ||
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
          player.SetDirection(Direction::STAY);
        }
      }
      player.Move(time / 1000);
    }

    view.setCenter(player.GetX(), player.GetY());
    main_window.setView(view);

    main_window.clear(Color(255, 255, 255));

    DrawMap(&main_window, map_tiles, tiles, map_sprite);

    main_window.draw(*player.GetSprite());
    main_window.display();
  }

  return 0;
}
