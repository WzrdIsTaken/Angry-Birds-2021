#include "../../EngineMethods.h"

#include "Level2.h"

void Level2::start()
{
  bcw::Renderer::renderSprite(&background_texture, &background_sprite, "Data/Images/lvl2.png");

  slingshot = bcw::SceneManagement::instanceScene(new Slingshot);
  slingshot->setup(sf::Vector2i(150, 435), this,
                   std::vector<Bird::BirdTypes> {Bird::BirdTypes::CHUCK, Bird::BirdTypes::RED, Bird::BirdTypes::CHUCK}, 5);

  level_number = 2;

  LevelBase::start();
}

void Level2::constructLevel()
{
  pig_count = 2;

  bcw::SceneManagement::instanceScene(new Pig)
    ->setup(sf::Vector2i(805, 490), 0.8, this);

  bcw::SceneManagement::instanceScene(new Pig)
    ->setup(sf::Vector2i(1000, 200), 1, this);

  bcw::SceneManagement::instanceScene(new Block)
    ->setup(sf::Vector2i(805, 525), 0, sf::Vector2f(0.5, 0.5), Block::BlockType::WOOD, Block::BlockShape::SQUARE);

  bcw::SceneManagement::instanceScene(new Block)
    ->setup(sf::Vector2i(725, 485), 90, sf::Vector2f(0.4, 1), Block::BlockType::WOOD, Block::BlockShape::RECTANGLE);

  bcw::SceneManagement::instanceScene(new Block)
    ->setup(sf::Vector2i(705, 565), 0, sf::Vector2f(0.7, 1), Block::BlockType::WOOD, Block::BlockShape::RECTANGLE);

  bcw::SceneManagement::instanceScene(new Block)
    ->setup(sf::Vector2i(1020, 250), 45, sf::Vector2f(1, 1), Block::BlockType::STONE, Block::BlockShape::RECTANGLE);

  bcw::SceneManagement::instanceScene(new Block)
    ->setup(sf::Vector2i(1000, 245), 0, sf::Vector2f(1, 1), Block::BlockType::STONE, Block::BlockShape::RECTANGLE);
}

void Level2::restartLevel()
{
  bcw::SceneManagement::changeScene(new Level2);
}