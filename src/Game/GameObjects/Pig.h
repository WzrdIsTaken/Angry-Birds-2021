#pragma once

#include "../../Engine.h"

class Pig : public bcw::Scene
{
 public:
  void setup(sf::Vector2i position, float _scale_modifier, bcw::Scene* _level);
  void onCollisionEnter(Scene* collision) override;

 private:
  bcw::Scene* level;

  sf::Texture texture;
  sf::Sprite sprite;

  float scale_modifier;
};