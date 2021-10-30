#include "../../EngineMethods.h"

#include "Poof.h"

void Poof::setup(sf::Vector2f position, float scale)
{
  for (int i = 1; i < 5; i++)
  {
    sf::Texture animation_frame;
    animation_frame.loadFromFile("Data/Images/OtherCoolSprites/Poof_" + std::to_string(i) + ".png");
    textures.push_back(animation_frame);
  }

  bcw::Renderer::renderSprite(&textures[0], &sprite, "Data/Images/OtherCoolSprites/Poof_1.png", position.x, position.y, scale, scale);
  animator.setup(&sprite, textures, 0.2);
}

void Poof::update(float dt)
{
  timer += dt;
  if (timer > LIFETIME)
  {
    setActiveState(false);
    bcw::Renderer::derenderDrawable(&sprite);
  }
}

// Might have a segfault with the animator, but I think it only matters in the debugger xd