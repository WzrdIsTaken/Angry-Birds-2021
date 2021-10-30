#include "EngineMethods.h"

// --- Engine Reference ---

bcw::Engine* bcw::EngineReference::engine;

// --- Scene  ---

// Used when you want to, eg, go from your main menu scene to game scene.
void bcw::SceneManagement::changeScene(Scene* new_scene)
{
  Renderer::stuff_to_draw.clear();
  engine->changeScene(new_scene);
}

// Used when you want to instantiate a scene (can be thought of as a gameobject in this case) in another scene.
bcw::Scene* bcw::SceneManagement::instanceScene(Scene* scene)
{
  engine->addScene(scene);
  return scene;
}

// Used when you want to check if a scene with a certain tag exits
bcw::Scene* bcw::SceneManagement::findScene(const std::string& tag)
{
  return engine->findScene(tag);
}

// Used when you want to delete a scene. You never want to use this on your current main scene, just instanced scenes. Return true/false depending on if the scene was deleted.
bool bcw::SceneManagement::deleteScene(Scene* scene)
{
  return engine->removeScene(scene);
}

// Used to pause the game.
void bcw::SceneManagement::setPauseState(bool new_state)
{
  engine->setPauseState(new_state);
}

// Returns if the game is paused.
bool bcw::SceneManagement::getPauseState()
{
  return engine->getPauseState();
}

// castData implementation is in EngineMethods.h

// --- User Input ---

// checkClick implementation is in EngineMethods.h

// Returns if the object is currently in the stuff_to_draw vector.
bool bcw::UserInput::checkIfObjectIsDrawn(sf::Drawable* object)
{
  // There has to be a better way to remove items you know longer want to be able to be clicked from the screen. This method and the one using bool checks are pretty bot.
  return std::count(Renderer::stuff_to_draw.begin(), Renderer::stuff_to_draw.end(), object);
}

// --- Rendering ---

std::vector<sf::Drawable*> bcw::Renderer::stuff_to_draw;
sf::RenderWindow* bcw::Renderer::window;

// Renders a sprite, loading the texture from the supplied path.
void bcw::Renderer::renderSprite(sf::Texture* texture, sf::Sprite* sprite, const std::string& path, float pos_x, float pos_y, float scale_x, float scale_y)
{
  texture->loadFromFile(path);
  sprite->setTexture(*texture);
  sprite->setScale(scale_x, scale_y);
  sprite->setPosition(pos_x == INFINITY ? float(window->getSize().x) / 2 - sprite->getGlobalBounds().width / 2 : pos_x,
                      pos_y == INFINITY ? float(window->getSize().y) / 2 - sprite->getGlobalBounds().height / 2 : pos_y);

  stuff_to_draw.push_back(sprite);
}

// Used to render a sprite with the texture has already been loaded.
void bcw::Renderer::renderSprite(sf::Texture* texture, sf::Sprite* sprite, float pos_x, float pos_y, float scale_x, float scale_y)
{
  sprite->setTexture(*texture);
  sprite->setScale(scale_x, scale_y);
  sprite->setPosition(pos_x == INFINITY ? float(window->getSize().x) / 2 - sprite->getGlobalBounds().width / 2 : pos_x,
                      pos_y == INFINITY ? float(window->getSize().y) / 2 - sprite->getGlobalBounds().height / 2 : pos_y);

  stuff_to_draw.push_back(sprite);
}

// Renders text, loading the font from the supplied path.
void bcw::Renderer::renderText(sf::Font* font, sf::Text* text, const std::string& path, const std::string& content, int size, sf::Color colour, float pos_x, float pos_y)
{
  font->loadFromFile(path);
  text->setString(content);
  text->setFont(*font);
  text->setCharacterSize(size);
  text->setFillColor(colour);
  text->setPosition(pos_x == INFINITY ? float(window->getSize().x) / 2 - text->getGlobalBounds().width / 2 : pos_x,
                    pos_y == INFINITY ? float(window->getSize().y) / 2 - text->getGlobalBounds().height / 2 : pos_y);

  stuff_to_draw.push_back(text);
}

// Used to render font when the font has already been loaded.
void bcw::Renderer::renderText(sf::Font* font, sf::Text* text, const std::string& content, int size, sf::Color colour, float pos_x, float pos_y)
{
  text->setString(content);
  text->setFont(*font);
  text->setCharacterSize(size);
  text->setFillColor(colour);
  text->setPosition(pos_x == INFINITY ? float(window->getSize().x) / 2 - text->getGlobalBounds().width / 2 : pos_x,
                    pos_y == INFINITY ? float(window->getSize().y) / 2 - text->getGlobalBounds().height / 2 : pos_y);

  stuff_to_draw.push_back(text);
}

// Used to update text content - useful if you want the text to say in the same position.
void bcw::Renderer::updateText(sf::Text* text, const std::string& newContent, float pos_x, float pos_y)
{
  // Todo: make it so the center of the text stays in the same place. Currently a scam method xd.
  float original_x = text->getPosition().x;
  float original_y = text->getPosition().y;

  text->setString(newContent);
  text->setPosition(pos_x == INFINITY ? original_x : pos_x,pos_y == INFINITY ? original_y : pos_y);
}

// Used to render a custom drawable (anything that inherits from sf::Drawable).
void bcw::Renderer::renderCustomDrawable(sf::Drawable* custom_drawable)
{
  stuff_to_draw.push_back(custom_drawable);
}

// Used to remove any drawable from the render vector.
void bcw::Renderer::derenderDrawable(sf::Drawable* drawable)
{
  stuff_to_draw.erase(std::remove(stuff_to_draw.begin(), stuff_to_draw.end(), drawable), stuff_to_draw.end());
}

// Used to flip a sprite on the x axis.
void bcw::Renderer::flipX(sf::Sprite* sprite)
{
  if (sprite->getTextureRect().left == 0)
  {
    sprite->setTextureRect(sf::IntRect(sprite->getLocalBounds().width, 0, -sprite->getLocalBounds().width, sprite->getLocalBounds().height));
  }
  else
  {
    sprite->setTextureRect(sf::IntRect(0, 0, sprite->getLocalBounds().width, sprite->getLocalBounds().height));
  }
}

// Used to flip a sprite on the y axis.
void bcw::Renderer::flipY(sf::Sprite* sprite)
{
  // Todo: Implement me!
}

// --- Physics ---

void bcw::Physics::addCollidableItem(sf::Sprite* sprite, Scene* scene)
{
  engine->addCollidableItem(sprite, scene);
}

void bcw::Physics::removeCollidableItem(sf::Sprite* sprite, Scene* scene)
{
  engine->removeCollidableItem(sprite, scene);
}

// --- MoreMaths ---

float bcw::MoreMath::clamp(float value, float upper, float lower)
{
  return std::min(upper, std::max(value, lower));
}

sf::Vector2f bcw::MoreMath::normalize(sf::Vector2f vector)
{
  float value = 1.0f / std::sqrt((vector.x * vector.x) + (vector.y * vector.y));
  vector.x *= value;
  vector.y *= value;
  return vector;
}