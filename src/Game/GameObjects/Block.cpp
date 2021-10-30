#include "../../EngineMethods.h"

#include "Block.h"

void Block::setup(sf::Vector2i position, float rotation, sf::Vector2f scale, Block::BlockType blockType, BlockShape blockShape)
{
  std::string file_path = "Data/Images/OtherCoolSprites/" + blockTypes[blockType] + blockShapes[blockShape] + ".png";
  bcw::Renderer::renderSprite(&texture, &sprite, file_path, position.x, position.y);
  sprite.rotate(rotation);
  sprite.setScale(scale);

  setTag("Block");
  bcw::Physics::addCollidableItem(&sprite, this);
}