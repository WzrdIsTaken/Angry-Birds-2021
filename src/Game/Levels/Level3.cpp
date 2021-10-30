#include "../../EngineMethods.h"

#include "Level3.h"

void Level3::start()
{
  bcw::Renderer::renderSprite(&background_texture, &background_sprite, "Data/Images/lvl3.png");

  slingshot = bcw::SceneManagement::instanceScene(new Slingshot);
  slingshot->setup(sf::Vector2i(150, 440), this,
                   std::vector<Bird::BirdTypes> {Bird::BirdTypes::BLUE, Bird::BirdTypes::CHUCK, Bird::BirdTypes::RED}, 11);

  level_number = 3;

  LevelBase::start();
}

void Level3::constructLevel()
{
  pig_count = 3;

  bcw::SceneManagement::instanceScene(new Pig)
    ->setup(sf::Vector2i(675, 452), 1.2, this);

  bcw::SceneManagement::instanceScene(new Pig)
    ->setup(sf::Vector2i(775, 350), 1, this);

  bcw::SceneManagement::instanceScene(new Pig)
    ->setup(sf::Vector2i(875, 250), 0.8, this);

  bcw::SceneManagement::instanceScene(new Block)
    ->setup(sf::Vector2i(675, 507), 0, sf::Vector2f(0.75, 1), Block::BlockType::STONE, Block::BlockShape::RECTANGLE);

  bcw::SceneManagement::instanceScene(new Block)
    ->setup(sf::Vector2i(775, 397), 0, sf::Vector2f(0.75, 1), Block::BlockType::STONE, Block::BlockShape::RECTANGLE);

  bcw::SceneManagement::instanceScene(new Block)
    ->setup(sf::Vector2i(875, 287), 0, sf::Vector2f(0.75, 1), Block::BlockType::STONE, Block::BlockShape::RECTANGLE);

  bcw::SceneManagement::instanceScene(new Block)
    ->setup(sf::Vector2i(725, 525), 0, sf::Vector2f(0.75, 0.75), Block::BlockType::STONE, Block::BlockShape::SQUARE);

  bcw::SceneManagement::instanceScene(new Block)
    ->setup(sf::Vector2i(815, 416), 90, sf::Vector2f(0.45, 1), Block::BlockType::STONE, Block::BlockShape::RECTANGLE);

  bcw::SceneManagement::instanceScene(new Block)
    ->setup(sf::Vector2i(925, 306), 90, sf::Vector2f(0.45, 1), Block::BlockType::STONE, Block::BlockShape::RECTANGLE);

  bcw::SceneManagement::instanceScene(new Block)
    ->setup(sf::Vector2i(1005, 304), 90, sf::Vector2f(1.4, 1.4), Block::BlockType::STONE, Block::BlockShape::RECTANGLE);
}

void Level3::restartLevel()
{
  bcw::SceneManagement::changeScene(new Level3);
}