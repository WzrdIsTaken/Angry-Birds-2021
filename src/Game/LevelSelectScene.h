#pragma once

#include "../Engine.h"

class LevelSelectScene : public bcw::Scene
{
 public:
  void start() override;
  void checkMousePressInput(sf::Vector2i click) override;

 private:
  static std::vector<std::string> readFile();

  sf::Font font;
  sf::Text title_text;

  sf::Texture background_texture;
  sf::Sprite background_sprite;

  sf::Texture back_button_texture;
  sf::Sprite back_button;

  sf::Texture level_button_textures[3];
  sf::Sprite level_buttons[3];
  sf::Text level_text[3];
  int number_of_levels = 3; // Could do something like sizeof(level_buttons) / sizeof(level_buttons[0]) but this is clearer
};