#pragma once

#include "../../Engine.h"

#include "Bird.h"

class Slingshot : public bcw::Scene
{
 public:
  void setup(sf::Vector2i position, bcw::Scene* _level, const std::vector<Bird::BirdTypes>& bird_types, float bird_queue_y_offset=0);
  void moveBird(sf::Vector2i mousePos);
  void launch();

  void receiveMessage(const std::string& id) override;

  sf::Sprite* getCurrentBirdSprite();
  bool getCurrentBirdLaunchedState() const;
  void useCurrentBirdSpecial();
  int getNumberOfBirds() const;

 private:
  Bird* getAndSetupBird();

  Bird* current_bird = nullptr;
  std::vector<Bird*> bird_queue;

  bcw::Scene* level = nullptr;

  sf::Texture texture;
  sf::Sprite sprite;

  sf::Vector2f default_bird_launch_position;
  sf::Vector2f bird_direction;
  float distance_from_start;

  const int DISTANCE_BETWEEN_BIRDS_IN_QUEUE = 50;
  const float MAX_DRAG_DISTANCE = 100;
  const float MIN_DRAG_DISTANCE = 50; // To make sure the bird doesn't fire if the user tries to reset the slingshot
};