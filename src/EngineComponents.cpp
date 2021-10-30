#include "EngineComponents.h"
#include "EngineMethods.h"

// --- Base ---

void bcw::Component::remove()
{
  bcw::SceneManagement::deleteScene(this);
}

// --- Animator ---

void bcw::Animator::setup(sf::Sprite* _sprite, const std::vector<sf::Texture>& _textures, float _tick)
{
  sprite = _sprite;
  textures = _textures;
  tick = _tick;

  bcw::SceneManagement::instanceScene(this);
}

void bcw::Animator::update(float dt)
{
  clock += dt;
  if (clock > tick)
  {
    // For some reason the animator doesn't work properly if the texture vector is the right size, so it has to be one bigger. But that means that this check must be against a value one less than the vectors size.
    // I have no idea why this is the case, its probably something super obvious and me just being dumb, but I'm too tired right now...
    // As long as its a consistent behaviour, its ok xD.

    if (current_frame < textures.size() - 1)
    {
      current_frame++;
    }
    else
    {
      current_frame = 0;
    }
    sprite->setTexture(textures[current_frame]);

    clock = 0;
  }
}