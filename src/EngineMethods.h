#pragma once

#include "Engine.h"

#include "cmath"

namespace bcw
{
  // Pretty bot, but better than having a bunch of engine references just floating around. Anyway, I'm the only one using this wrapper so its not a huge issue - just bad style and
  // something to improve next time. More planning and research into other wrappers / engines is probably the solution :D.
  class EngineReference
  {
   protected:
    static Engine* engine;

    friend Engine;
  };

  // Handles all scene related stuff.
  class SceneManagement : EngineReference
  {
   public:
    static void changeScene(Scene* new_scene);
    static bcw::Scene* instanceScene(Scene* scene);
    static bool deleteScene(Scene* scene);
    static bcw::Scene* findScene(const std::string& tag);
    static void setPauseState(bool new_state);
    static bool getPauseState();

    // It seems like templates don't quite work with .h / .cpp files. I'm sure there is a clean way around this problem, but I can solve that later if its ever an issue.

    // Use this method to streamline casting data after getting it from receiveMessage(). Use like: type variable = typecastData<type>(data);.
    template<typename T, typename U>
    static T castData(U data)
    {
      return *static_cast<T*>(data);
    }

    // Use this method to instance scenes when circular dependency is not an issue (returns the scene as its derived type)
    template<typename T>
    static T* instanceScene(T* scene)
    {
      engine->addScene(scene);
      return scene;
    }
  };

  // Handles all user input stuff.
  class UserInput
  {
   public:
    // This method returns true if the passed in object has the cursors position within its global bounds.
    template <typename T>
    static bool checkClick(sf::Vector2i click, T* object)
    {
      if (!object)
      {
        return false;
      }

      return object->getGlobalBounds().contains(click.x, click.y) && checkIfObjectIsDrawn(object);
    }

   private:
    static bool checkIfObjectIsDrawn(sf::Drawable* object);
  };

  // Handles all - you guessed it - rendering related stuff.
  class Renderer
  {
   public:
    static void renderSprite(sf::Texture* texture, sf::Sprite* sprite, const std::string& path, float pos_x = 0, float pos_y = 0,
                             float scale_x = 1, float scale_y = 1);
    static void renderSprite(sf::Texture* texture, sf::Sprite* sprite, float pox_x = 0, float pos_y = 0, float scale_x = 1, float scale_y = 1);

    static void renderText(sf::Font* font, sf::Text* text, const std::string& path, const std::string& content, int size, sf::Color colour,
                           float pos_x = INFINITY, float pos_y = INFINITY);
    static void renderText(sf::Font* font, sf::Text* text, const std::string& content, int size, sf::Color colour,
                           float pos_x = INFINITY, float pos_y = INFINITY);
    static void updateText(sf::Text* text, const std::string& newContent, float pos_x = INFINITY, float pos_y = INFINITY);

    static void renderCustomDrawable(sf::Drawable* custom_drawable);

    static void derenderDrawable(sf::Drawable* drawable);

    static void flipX(sf::Sprite* sprite);
    static void flipY(sf::Sprite* sprite);

    static sf::RenderWindow* window;

   private:
    static std::vector<sf::Drawable*> stuff_to_draw;

    friend Engine;
    friend SceneManagement;
    friend UserInput;
  };

  // All stuff to do with physics operations goes through here.
  class Physics : EngineReference
  {
   public:
    // Unless you're doing something advanced, then its best to leave this method alone. It is automatically called in the setup function of the Collider component.
    static void addCollidableItem(sf::Sprite* sprite, Scene* scene);
    // Unless you're doing something advanced, then its best to leave this method alone. It is automatically called in end function of the Collider component.
    static void removeCollidableItem(sf::Sprite* sprite, Scene* scene);
  };

  // More maths
  class MoreMath
  {
   public:
    // https://stackoverflow.com/questions/21656574/why-is-there-no-clamp-function-in-math-h
    static float clamp(float value, float upper, float lower);
    static sf::Vector2f normalize(sf::Vector2f vector);
  };
}

// http://www.technologicalutopia.com/sourcecode/xnageometry/vector2.cs.htm (lots of vector methods here if needed in future)