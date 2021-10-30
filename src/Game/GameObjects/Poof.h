#pragma once

#include "../../Engine.h"
#include "../../EngineComponents.h"

class Poof : public bcw::Scene
{
 public:
  void setup(sf::Vector2f position, float scale);
  void update(float dt) override;

 private:
  std::vector<sf::Texture> textures;
  sf::Sprite sprite;
  bcw::Animator animator;

  float timer = 0;
  const float LIFETIME = 0.8;
};