#pragma once

#include "../../Engine.h"

#include "../GameObjects/Slingshot.h"
#include "../GameObjects/Pig.h"
#include "../GameObjects/Block.h"

class LevelBase : public bcw::Scene
{
 public:
  void start() override;
  void update(float dt) override;
  void checkMousePressInput(sf::Vector2i click) override;
  void checkMouseReleaseInput(sf::Vector2i click) override;
  void receiveMessage(const std::string& id) override;

 protected:
  virtual void constructLevel() {};
  virtual void restartLevel() {}; // Probs a better way of doing this (I wish I could just use the level_number but reflection doesn't look easy in c++)
  void updateScore(int increase);
  void gameOver();

  Slingshot* slingshot;

  sf::Texture background_texture;
  sf::Sprite background_sprite;

  int pig_count = 0;
  int level_number = 0;

 private:
  sf::Texture pause_button_texture;
  sf::Sprite pause_button;

  // These text objects are also used for the game over state because the structure is basically the same
  sf::Font font;
  sf::Text score_text;
  sf::Text pause_text;
  sf::Text resume_text;
  sf::Text restart_text;
  sf::Text exit_text;

  int score = 0;
  bool holding = false;
  bool game_over = false;

  const sf::Color disabledColour = sf::Color(200, 200, 200);
};