#include "../../EngineMethods.h"

#include "Pig.h"

#include "Poof.h"

void Pig::setup(sf::Vector2i position, float _scale_modifier, bcw::Scene* _level)
{
  bcw::Renderer::renderSprite(&texture, &sprite, "Data/Images/OtherCoolSprites/Pig.png", position.x, position.y,
                              0.075f * _scale_modifier, 0.075f * _scale_modifier);

  level = _level;
  scale_modifier = _scale_modifier;

  setTag("Pig");
  bcw::Physics::addCollidableItem(&sprite, this);
}

void Pig::onCollisionEnter(Scene* collision)
{
  if (collision->getTag() == "Bird")
  {
    level->sendMessage("PIG_HIT");

    bcw::SceneManagement::instanceScene(new Poof)->setup(sprite.getPosition(), 3 * scale_modifier);

    bcw::Renderer::derenderDrawable(&sprite);
    setActiveState(false);
  }
}