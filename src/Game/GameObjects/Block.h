#pragma once

#include "../../Engine.h"

class Block : public bcw::Scene
{
 public:
  enum BlockType { WOOD, STONE };
  enum BlockShape { SQUARE, RECTANGLE };

  void setup(sf::Vector2i position, float rotation, sf::Vector2f scale, BlockType blockType, BlockShape blockShape);

 private:
  sf::Texture texture;
  sf::Sprite sprite;

  std::map<BlockType, std::string> blockTypes
  {
    {WOOD, "Wood"}, {STONE, "Stone"}
  };
  std::map<BlockShape, std::string> blockShapes
  {
    {SQUARE, "Square"}, {RECTANGLE, "Rectangle"}
  };
};