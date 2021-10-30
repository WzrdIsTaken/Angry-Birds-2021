#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// Ben's cool wrapper - great name I know.
namespace bcw
{
  // In bcw, like Godot, scenes and gameobjects are the same. If you want the behaviour of a gameobject, instance a scene rather than changing to it.
  class Scene
  {
   public:
    virtual void start() {};
    virtual void end() {};
    virtual void update(float dt) {};
    virtual void checkMousePressInput(sf::Vector2i click) {};
    virtual void checkMouseReleaseInput(sf::Vector2i click) {};
    virtual void checkKeyboardInput(int key_code) {};

    // Could use int id's so can use a switch statement in receive, but imo strings are clearer. Might change if I find an object needs to receive loads of different messages.

    void sendMessage(const std::string& id);
    // Note: It is the users responsibility to manage the data they send. push_back a reference (& if the data is not a pointer) to the data you want to send.
    void sendMessage(const std::string& id, const std::vector<void*>& data);

    bool getDontDestroyOnLoad() const;
    void setDontDestroyOnLoad(bool new_state);

    bool getActiveState() const;
    void setActiveState(bool new_state);

    std::string getTag() const;
    void setTag(const std::string& new_tag);

    virtual void onCollisionEnter(Scene* collision) {};
    virtual void onCollisionExit(Scene* collision) {};

    virtual ~Scene() = default; // end() should be used in derived scenes, but deleting doesn't work properly if you don't have a virtual destructor https://stackoverflow.com/a/461224/8890269.

   private:
    virtual void receiveMessage(const std::string& id) {};
    // Note: It is the users responsibility to manage the data they receive.
    virtual void receiveMessage(const std::string& id, const std::vector<void*>& data) {};

    bool dont_destroy_on_load = false;
    bool is_active = true;
    std::string tag;
  };

  // The Engine class should never be accessed by anything other than EngineMethods.
  class Engine
  {
   public:
    explicit Engine(sf::RenderWindow& window, Scene* first_scene);
    ~Engine() = default;
    void update(float dt);
    void render();
    void mouseClicked();
    void mouseReleased();
    void keyPressed(int key_code);

    void changeScene(Scene* scene);
    void addScene(Scene* scene);
    bool removeScene(Scene* scene);

    bool getPauseState() const;
    void setPauseState(bool new_state);

    void addCollidableItem(sf::Sprite* sprite, Scene* scene);
    void removeCollidableItem(sf::Sprite* sprite, Scene* scene);

    Scene* findScene(const std::string& tag);

   private:
    void checkCollisions();

    sf::RenderWindow& window;
    std::vector<Scene*> scenes;

    bool paused = false;

    std::map<sf::Sprite*, Scene*> colliders;
    std::vector<std::pair<Scene*, Scene*>> current_collisions;
  };
}