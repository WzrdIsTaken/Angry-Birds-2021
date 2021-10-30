#pragma once

#include "../Engine.h"

#include "GameObjects/MusicManager.h" // Because MusicManager doesn't need a ref back to the MainMenu, can do this without circular dependency issues.
                                      // Can do this in other places as well (ie, not storing GameObjects as Scenes and directly accessing their functionality
                                      // rather than using SendMessage).

class MainMenuScene : public bcw::Scene
{
 public:
  void start() override;
  void checkMousePressInput(sf::Vector2i click) override;

 private:
  MusicManager* musicManager = nullptr;

  sf::Font font;
  sf::Text title_text;
  sf::Text play_text;
  sf::Text exit_text;

  sf::Texture background_texture;
  sf::Sprite background_sprite;

  sf::Texture music_button_texture;
  sf::Sprite music_button;
  sf::Texture sound_fx_button_texture;
  sf::Sprite sound_fx_button;

  const sf::Color disabledColour = sf::Color(200, 200, 200);
};