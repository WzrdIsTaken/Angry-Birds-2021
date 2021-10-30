#include "../../EngineMethods.h"

#include "Level1.h"

void Level1::start()
{
  bcw::Renderer::renderSprite(&background_texture, &background_sprite, "Data/Images/lvl1.png");

  slingshot = bcw::SceneManagement::instanceScene(new Slingshot);
  slingshot->setup(sf::Vector2i(150, 460), this,
                   std::vector<Bird::BirdTypes> {Bird::BirdTypes::RED, Bird::BirdTypes::RED, Bird::BirdTypes::RED});

  level_number = 1;

  LevelBase::start();
}

void Level1::constructLevel()
{
  // Could have some sort of file system for this (ie loading levels from something like a tile-map),
  // but (and maybe its just because I'm most comfortable with engines that use this structure) I
  // like the concept of scenes. It does result in a bit of code repetition (ie in the start method)
  // and the slightly awkward restartLevel implementation, but overall I think its clearer.

  // If we were doing something more complex, I would definitely read from a file but as there aren't
  // that many assets per scene its ok.

  pig_count = 1;

  bcw::SceneManagement::instanceScene(new Pig)
    ->setup(sf::Vector2i(775, 454), 1, this);

  bcw::SceneManagement::instanceScene(new Block)
    ->setup(sf::Vector2i(700, 500), 0, sf::Vector2f(1, 1), Block::BlockType::WOOD, Block::BlockShape::RECTANGLE);

  bcw::SceneManagement::instanceScene(new Block)
    ->setup(sf::Vector2i(710, 517), 90, sf::Vector2f(0.4, 0.5), Block::BlockType::WOOD, Block::BlockShape::RECTANGLE);

  bcw::SceneManagement::instanceScene(new Block)
    ->setup(sf::Vector2i(904, 517), 90, sf::Vector2f(0.5, 0.5), Block::BlockType::WOOD, Block::BlockShape::RECTANGLE);
}

void Level1::restartLevel()
{
  bcw::SceneManagement::changeScene(new Level1);
}