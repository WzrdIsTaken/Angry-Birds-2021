#include "Engine.h"
#include "EngineMethods.h"

// --- Scene ---

void bcw::Scene::sendMessage(const std::string& id)
{
  receiveMessage(id);
}

void bcw::Scene::sendMessage(const std::string& id, const std::vector<void*>& data)
{
  receiveMessage(id, data);
}

bool bcw::Scene::getDontDestroyOnLoad() const
{
  return dont_destroy_on_load;
}

void bcw::Scene::setDontDestroyOnLoad(bool new_state)
{
  dont_destroy_on_load = new_state;
}

bool bcw::Scene::getActiveState() const
{
  return is_active;
}

void bcw::Scene::setActiveState(bool new_state)
{
  is_active = new_state;
}

std::string bcw::Scene::getTag() const
{
  return tag;
}

void bcw::Scene::setTag(const std::string& new_tag)
{
  tag = new_tag;
}

// --- Engine ---

// Called when the engine is initialised in main.cpp. Seeds random, assigns some important variables and loads the first scene.
bcw::Engine::Engine(sf::RenderWindow& game_window, Scene* first_scene): window(game_window)
{
  srand(time(nullptr));
  EngineReference::engine = this;
  Renderer::window = &window;

  addScene(first_scene);
}

// Called every frame from main.cpp. Calls update() on every scene. Use dt for framerate independent tasks.
void bcw::Engine::update(float dt)
{
  if (!paused)
  {
    for (auto& scene : scenes)
    {
      if (scene && scene->getActiveState())
      {
        scene->update(dt);
      }
    }
    checkCollisions();
  }
}

// Called every frame from main.cpp. Renders all drawables in the stuff_to_draw vector.
void bcw::Engine::render()
{
  for (auto& item : Renderer::stuff_to_draw)
  {
    window.draw(*item);
  }
}

// Called from main.cpp when a mouse button is pressed. Calls checkMousePressInput() on every scene.
void bcw::Engine::mouseClicked()
{
  // For some reason, if I do the loop when there is more than once scene (ie, scenes are instanced) then I get a segmentation fault (see debugger).
  // -1073741819 (0xC0000005) https://stackoverflow.com/a/53485066/8890269
  // The fault triggers from the checkMousePressInput or checkKeyboardInput function - even if setActiveState(false) has been called on the scene.
  // Not exactly sure why this is happening, but I'm moving on for now as its not a problem for this game.
  scenes[0]->checkMousePressInput(sf::Mouse::getPosition(window));

  /* Something like this would be ideal
  for (auto& scene : scenes)
  {
    if (scene->getActiveState()) scene->checkMousePressInput(sf::Mouse::getPosition(window));
  }
   */
}

// Called from main.cpp when a mouse button is released. Calls checkMouseReleaseInput() on every scene.
void bcw::Engine::mouseReleased()
{
  // I assume the same problem as with mouseClicked
  scenes[0]->checkMouseReleaseInput(sf::Mouse::getPosition(window));

  /* Something like this would be ideal
  for (auto& scene : scenes)
  {
    if (scene->getActiveState()) scene->checkMouseReleaseInput(sf::Mouse::getPosition(window));
  }
   */
}

// Called from main.cpp when a key is pressed. Calls checkKeyboardInput() on every scene.
void bcw::Engine::keyPressed(int key_code)
{
  // Same problem as with mouseClicked
  scenes[0]->checkKeyboardInput(key_code);

  /* Something like this would be ideal
  for (auto& scene : scenes)
  {
    if (scene->getActiveState()) scene->checkKeyboardInput(key_code);
  }
   */
}

// Called from EngineMethods changeScene. Deletes all current scenes and loads a new one.
void bcw::Engine::changeScene(Scene* new_scene)
{
  // Swap not clear https://www.techiedelight.com/delete-vector-free-memory-cpp/
  std::map<sf::Sprite*, Scene*>().swap(colliders);
  std::vector<std::pair<Scene*, Scene*>>().swap(current_collisions);

  std::vector<Scene*> dont_destroy_scenes;
  for (auto& scene : scenes)
  {
    if (scene->getDontDestroyOnLoad())
    {
      dont_destroy_scenes.push_back(scene);
    }
    else
    {
      delete scene;
    }
  }

  // Because of the issue with mouseClicked and co, can't just to dont_destroy_scenes.swap(scenes) as those methods work by looking at the first scene in the vector
  // Therefore, have to do this. It's not great but works.

  std::vector<Scene*>().swap(scenes);
  scenes.push_back(new_scene);
  for (auto& scene : dont_destroy_scenes)
  {
    scenes.push_back(scene);
  }
  scenes[0]->start();
}

// Called from EngineMethods instanceScene. Adds a new scene to the scenes vector.
void bcw::Engine::addScene(Scene* scene)
{
  scenes.push_back(scene);
  scene->start();
}

// Called from EngineMethods deleteScene. Tries to delete the scene from the scenes vector, returning true/false depending on if it was a success.
bool bcw::Engine::removeScene(Scene* scene)
{
  auto it = std::find(scenes.begin(), scenes.end(), scene);
  if (it != scenes.end())
  {
    scene->end();
    scene->setActiveState(false);
    delete *it;
    scenes.erase(it);

    return true;
  }

  return false;
}

// Called from EngineMethods getPauseState. Returns the pause state.
bool bcw::Engine::getPauseState() const
{
  return paused;
}

// Called EngineMethods setPauseState. Sets the pause state.
void bcw::Engine::setPauseState(bool new_state)
{
  paused = new_state;
}

// Called from EngineMethods addCollidableItem. Adds a sprite to the colliders map.
void bcw::Engine::addCollidableItem(sf::Sprite* sprite, Scene* scene)
{
  colliders.emplace(sprite, scene);
}

// Called from EngineMethods removeCollidableItems. Removes a sprite from the colliders map and from any active collisions.
void bcw::Engine::removeCollidableItem(sf::Sprite* sprite, Scene* scene)
{
  for (int i = 0; i < current_collisions.size(); i++)
  {
    auto collision = current_collisions[i];

    if (collision.first == scene || collision.second == scene)
    {
      if (collision.first == scene)
      {
        collision.second->onCollisionExit(collision.first);
      }
      else
      {
        collision.first->onCollisionExit(collision.second);
      }

      current_collisions.erase(current_collisions.begin() + i);
    }
  }

  colliders.erase(sprite);
}

// Very basic and inefficient collision detection - basically just so I can get something working and can move on. Will optimise in the future if needed.
void bcw::Engine::checkCollisions()
{
  if (colliders.empty()) return;

  for (auto& collider_1 : colliders)
  {
    for (auto& collider_2 : colliders)
    {
      // In the future might also want to check for empty tags? These scenes would collide with anything.
      if (collider_1 == collider_2 || collider_1.second->getTag() == collider_2.second->getTag() ||
          !collider_1.second->getActiveState() || !collider_2.second->getActiveState())
      {
        continue;
      }

      bool colliding = collider_1.first->getGlobalBounds().intersects(collider_2.first->getGlobalBounds());

      auto collision_pair = std::make_pair(collider_1.second, collider_2.second);
      auto it = std::find(current_collisions.begin(), current_collisions.end(), collision_pair);
      bool already_colliding = it != current_collisions.end();

      if (colliding && already_colliding || !colliding && !already_colliding)
      {
        continue;
      }
      else if (colliding)
      {
        current_collisions.push_back(collision_pair);
        collider_1.second->onCollisionEnter(collider_2.second);
      }
      else
      {
        current_collisions.erase(it);
        collider_1.second->onCollisionExit(collider_2.second);
      }
    }
  }
}

// Checks to see if a scene with a certain tag exits (could also do this but search by type if this functionality was ever needed)
bcw::Scene* bcw::Engine::findScene(const std::string& tag)
{
  for (auto& scene : scenes)
  {
    if (scene->getTag() == tag)
    {
      return scene;
    }
  }

  return nullptr;
}

// A useful function (if ever needed) would basically be this  ^ except 'findScenes' and it could return a vector of all the scenes