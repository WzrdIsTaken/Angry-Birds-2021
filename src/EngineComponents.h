#pragma once

#include "Engine.h"

// Components are things you can 'add' onto objects to easily give them extra functionality. They should have a 'HAS-A' relationship.
// Like all objects in bcw, components are also 'scenes'. This means they are really easy to manipulate and automatically follow all the game rules / states - eg: pausing.
namespace bcw
{
  // Note: I know that I could / probs should have more components, eg SpriteRenderer and TextRenderer - but I'm happy with the way things are working rn and I think (hope :D)
  // that after this project we only have one more with sfml. If we have to more, I'll probs do some work streamlining the component system.

  // Base
  class Component : public Scene
  {
   public:
    void remove();

    // Todo: Add enabling / disabling
  };

  // Animates a sprite by iterating thought an array of textures.
  class Animator : public Component
  {
   public:
    void setup(sf::Sprite* _sprite, const std::vector<sf::Texture>& _textures, float _tick);
    void update(float dt) override;

   private:
    sf::Sprite* sprite = nullptr;
    std::vector<sf::Texture> textures;

    float tick;
    float clock;
    int current_frame = 0;
  };

  // Collider was a component, but due to a bug I didn't know how to solve I took the lazy route and just made it so you have to use bcw::Physics::addCollidableItem instead.
  // Note about future implementation of collider component below:

  /* If working on another wrapper, or for game engine programming in yr2, I would like to have function pointers instead of the base Scene class containing
     * onCollisionEnter/Exit. Could have something like...
     * void(*_on_collision_enter_callback)(Collider* collision)
     * ...and pass in a reference to the function you want to call when the sprite intersects with something - like Godot not Unity (so all scenes don't have a method that they
     * might never use). However, because of the current file structure this would cause circular dependency. Going with a virtual OnCollisionEnter/Exit function isn't really a
     * massive problem - just something to consider next time. */
}