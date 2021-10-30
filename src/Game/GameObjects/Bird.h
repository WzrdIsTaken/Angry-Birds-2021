#pragma once

#include "../../Engine.h"

class Bird : public bcw::Scene
{
 public:
  enum BirdTypes { RED, CHUCK, BLUE };

  void setup(sf::Vector2f startPos, BirdTypes _birdType, bcw::Scene* _slingshot, sf::Vector2f initial_velocity=sf::Vector2f(0,0));
  void launch(sf::Vector2f direction, float force);
  void special();
  void update(float dt) override;
  void onCollisionEnter(Scene* collision) override;

  sf::Sprite* getSprite();
  bool getLaunched() const;

 private:
  bcw::Scene* slingshot;

  BirdTypes birdType;

  sf::Texture texture;
  sf::Sprite sprite;

  sf::Vector2f velocity;

  bool launched = false;
  bool next_bird_loaded = false;
  bool used_special = false;
  bool clone = false;

  const float FORCE_MULTIPLIER = 3;
  const float MASS = 1;
  const float DRAG = 20;
  const float GROUND_HEIGHT = 560;

  const float CHUCK_BOOST_AMOUNT = 200;
};