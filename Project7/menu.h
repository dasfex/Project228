#ifndef PROJECT228_MENU_H
#define PROJECT228_MENU_H

#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include "main_headers.h"

using std::vector;

bool is_menu_was_open = false;
int volume = 50;

void CheckMousePos(int num, int& ret, int x_1, int y_1, int x_2, int y_2,
                   sf::RenderWindow* window, sf::Sprite* menu, int c1, int c2,
                   int c3) {
  if (sf::IntRect(x_1, y_1, x_2, y_2).contains(
      sf::Mouse::getPosition(*window))) {
    menu->setColor(sf::Color(c1, c2, c3));
    ret = num;
  }
}

void GameEnd(sf::RenderWindow* window,
             sf::Music* music,
             std::string music_path,
             std::string img_path,
             int x,
             int y,
             sf::Clock* timer) {

  auto play_time = timer->getElapsedTime().asMilliseconds() + 13000;
  music->stop();
  music->openFromFile(music_path);
  music->play();
  sf::Texture game_over_texture;
  game_over_texture.loadFromFile(img_path);
  sf::Sprite game_over(game_over_texture);

  if (music_path == "files/music/game_over.ogg") {
    game_over.setScale(1.05, 1.05);
  } else {
    game_over.setScale(2, 2);
  }
  game_over.setPosition(x, y);

  while (play_time >= timer->getElapsedTime().asMilliseconds()) {
    window->draw(game_over);
    window->display();
  }

  exit(0);
}

void Settings(sf::RenderWindow* window, sf::Music* music,
              sf::Music* menu_music, int coor_x, int coor_y) {

  std::fstream mus_file_name("files/musicnames.txt");
  size_t music_textures_size;
  mus_file_name >> music_textures_size;

  std::vector<sf::Texture> music_textures(music_textures_size);
  std::vector<std::string> mus_names(music_textures_size);

  for (auto& name : mus_names) {
    mus_file_name >> name;
  }

  sf::Texture type_music_1_texture, type_music_2_texture, setting_background;

  sf::Font font;
  font.loadFromFile("files/Samson.ttf");
  sf::Text vol("", font, 100);
  vol.setFillColor(sf::Color::Magenta);
  vol.setPosition(800 + coor_x, 1000 + coor_y);

  // Опять стремный блок
  setting_background.loadFromFile("img/setting_bg.jpg");
  for (size_t i = 0; i < music_textures_size; ++i) {
    music_textures[i].loadFromFile("img/" + mus_names[i] + ".png");
  }
  type_music_1_texture.loadFromFile("img/MenuMusic.png");
  type_music_2_texture.loadFromFile("img/MusicGame.png");

  vector<std::string> all_music(music_textures_size);
  for (size_t i = 0; i < music_textures_size; ++i) {
    all_music[i] = "files/music/" + mus_names[i] + ".ogg";
  }

  sf::Sprite settings(setting_background),
      type_1(type_music_1_texture), type_2(type_music_2_texture);
  std::vector<sf::Sprite> music_(music_textures_size);
  for (size_t i = 0; i < music_.size(); ++i) {
    music_[i].setTexture(music_textures[i]);
  }

  vector<sf::Sprite> musics1 = {type_1};
  for (const auto& music__ : music_) {
    musics1.push_back(music__);
  }

  vector<sf::Sprite> musics2 = {type_2};
  for (const auto& music__ : music_) {
    musics2.push_back(music__);
  }

  settings.setScale(1.05, 1.15);
  settings.setPosition(70 + coor_x, 90 + coor_y);
  int music_num = 0;

  int x = 240 + coor_y;

  for (int i = 0; i < 7; i++) {
    musics1[i].setScale(2, 2);
    musics2[i].setScale(2, 2);
    if (i < 5) {
      musics1[i].setPosition(200 + coor_x, x);
      musics2[i].setPosition(1200 + coor_x, x);
    } else {
      musics1[i].setPosition(180 + coor_x, x);
      musics2[i].setPosition(1180 + coor_x, x);
    }
    if (i < 1) {
      musics1[i].setColor(sf::Color(255, 0, 255));
      musics2[i].setColor(sf::Color(255, 0, 255));
    }
    x += 100;
  }

  while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
    for (int i = 1; i < 7; i++) {
      musics1[i].setColor(sf::Color::White);
      musics2[i].setColor(sf::Color::White);
    }

    music_num = 0;
    bool sound_down = false, sound_up = false;
    window->clear(sf::Color(129, 181, 221));

    int x = 200;
    for (int i = 2; i <= 7; i++) {
      if (i < 5) {
        CheckMousePos(i - 2, music_num, 200, x, 550, 130, window,
                      &musics1[i - 1], 139, 0, 0);
        CheckMousePos(i + 4, music_num, 1200, x, 550, 130, window,
                      &musics2[i - 1], 139, 0, 0);
      } else {
        CheckMousePos(i - 2, music_num, 180, x, 550, 130, window,
                      &musics1[i - 1], 139, 0, 0);
        CheckMousePos(i + 4, music_num, 1180, x, 550, 130, window,
                      &musics2[i - 1], 139, 0, 0);
      }
      x += 140;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      for (int i = 0; i <= 11; i++) {
        if (i == music_num) {
          if (i > 5) {
            music->openFromFile(all_music[i % 6]);
          } else {
            menu_music->openFromFile(all_music[i]);
            menu_music->play();
          }
        }
      }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F9)) {
      volume = 0;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F10)) {
      volume = 50;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F11)) {
      volume = 100;
    }

    music->setVolume(volume);
    menu_music->setVolume(volume);

    window->draw(settings);
    vol.setString("Volume: " + std::to_string(volume));
    window->draw(vol);

    for (sf::Sprite& el : musics1) {
      window->draw(el);
    }

    for (sf::Sprite& el : musics2) {
      window->draw(el);
    }

    window->display();
  }
}

void Menu(sf::RenderWindow* window, sf::Music* music, sf::Music* menu_music,
          int coor_x = 0, int coor_y = 0) {

  sf::Texture menu_texture1, menu_texture2, menu_texture3, menu_texture4,
      menu_background;

  if (!is_menu_was_open) {
    menu_music->openFromFile("files/music/LPNumb.ogg");
    music->openFromFile("files/music/GameOfThrone.ogg");
    menu_music->setVolume(volume);
    music->setVolume(volume);
  } else {
    music->stop();
  }

  menu_music->setLoop(true);
  menu_music->play();

  if (is_menu_was_open) {
    menu_texture1.loadFromFile("img/continue.png");
  } else {
    menu_texture1.loadFromFile("img/new_game.png");
  }
  menu_texture2.loadFromFile("img/settings.png");
  menu_texture3.loadFromFile("img/creators.png");
  menu_texture4.loadFromFile("img/exit.png");
  menu_background.loadFromFile("img/background.jpg");

  sf::Sprite menu_1(menu_texture1), menu_2(menu_texture2),
      menu_3(menu_texture3), menu_4(menu_texture4),
      background(menu_background);

  vector<sf::Sprite> menu_batton = {menu_1, menu_2, menu_3, menu_4};
  bool is_menu_open = true;
  int menu_num = 0;

  background.setScale(0.75, 0.75);
  background.setPosition(100 + coor_x, 100 + coor_y);

  int x = 670 + coor_y;

  for (int i = 0; i < 4; i++) {
    if (i == 0 && is_menu_was_open) {
      menu_batton[i].setScale(2, 2);
      menu_batton[i].setPosition(450 + coor_x, x);
    } else {
      menu_batton[i].setScale(2, 2);
      menu_batton[i].setPosition(430 + coor_x, x);
    }
    x += 100;
  }

  while (is_menu_open) {
    for (sf::Sprite& el : menu_batton) {
      el.setColor(sf::Color(139, 0, 0));
    }
    menu_num = 0;
    window->clear(sf::Color(129, 181, 221));

    int x = 650;
    for (int i = 1; i <= 4; i++) {
      if (i == 1) {
        CheckMousePos(i, menu_num, 450, x, 600, 100, window,
                      &menu_batton[i - 1], 0, 0, 0);
      } else {
        CheckMousePos(i, menu_num, 430, x, 600, 100, window,
                      &menu_batton[i - 1], 0, 0, 0);
      }
      x += 100;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      if (menu_num == 1) {
        is_menu_open = false;
      } else if (menu_num == 2) {
        Settings(window, music, menu_music, coor_x, coor_y);
      } else if (menu_num == 3) {
        sf::Texture creators_texture;
        creators_texture.loadFromFile("img/creators.jpg");
        sf::Sprite creators(creators_texture);
        creators.setPosition(70 + coor_x, 90 + coor_y);
        window->draw(creators);
        window->display();
        while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape));
      } else if (menu_num == 4) {
        window->close();
        is_menu_open = false;
      }
    }

    window->draw(background);

    for (sf::Sprite& el : menu_batton) {
      window->draw(el);
    }

    window->display();
    if (!is_menu_open) {
      menu_music->stop();
    }
  }

  music->play();
  is_menu_was_open = true;
}

#endif  // PROJECT228_MENU_H
