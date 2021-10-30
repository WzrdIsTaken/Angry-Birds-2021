#include "../../EngineMethods.h"

#include "Slingshot.h"

void Slingshot::setup(sf::Vector2i position, bcw::Scene* _level, const std::vector<Bird::BirdTypes>& bird_types, float bird_queue_y_offset)
{
  bcw::Renderer::renderSprite(&texture, &sprite, "Data/Images/OtherCoolSprites/Slingshot.png", position.x, position.y, 0.75, 0.75);

  default_bird_launch_position = sf::Vector2f(sprite.getPosition().x + 10, sprite.getPosition().y - 5);
  level = _level;

  for (int i = 0; i < bird_types.size(); i++)
  {
    Bird* b = bcw::SceneManagement::instanceScene(new Bird);
    b->setup(sf::Vector2f(position.x - 25 - (DISTANCE_BETWEEN_BIRDS_IN_QUEUE * i), position.y + 100.0f + bird_queue_y_offset), bird_types[i], this);
    bird_queue.push_back(b);
  }

  current_bird = getAndSetupBird();
}

void Slingshot::moveBird(sf::Vector2i mousePos)
{
  sf::Vector2f bird_position = sf::Vector2f(mousePos.x, mousePos.y);

  // ↓ This is a very bad (hopefully temporary) solution. I know that you can get the relative mouse position by passing in window
  // ↓ to getMousePosition but can't do that with RenderWindow and I don't know a better solution yet.
  bird_position.x -= 430;
  bird_position.y -= 230;

  sf::Vector2f slingshot_to_mouse = bird_position - default_bird_launch_position;
  bird_direction = sf::Vector2f(
    default_bird_launch_position.x + bcw::MoreMath::clamp(slingshot_to_mouse.x, MAX_DRAG_DISTANCE, -MAX_DRAG_DISTANCE),
    default_bird_launch_position.y + bcw::MoreMath::clamp(slingshot_to_mouse.y, MAX_DRAG_DISTANCE, -MAX_DRAG_DISTANCE));
  distance_from_start = std::sqrt((slingshot_to_mouse.x * slingshot_to_mouse.x) + (slingshot_to_mouse.y * slingshot_to_mouse.y));
  current_bird->getSprite()->setPosition(bird_direction);
}

void Slingshot::launch()
{
  if (distance_from_start > MIN_DRAG_DISTANCE)
  {
    current_bird->launch(default_bird_launch_position - bird_direction, distance_from_start > MAX_DRAG_DISTANCE ? MAX_DRAG_DISTANCE : distance_from_start);
  }
  else
  {
    bird_direction = sf::Vector2f(0,0);
    current_bird->getSprite()->setPosition(default_bird_launch_position);
  }
}

Bird* Slingshot::getAndSetupBird()
{
  if (bird_queue.empty())
  {
    return nullptr;
  }

  Bird* bird_to_return = bird_queue[0];
  bird_to_return->getSprite()->setPosition(default_bird_launch_position);
  bird_queue.erase(bird_queue.begin());

  for (auto& b : bird_queue)
  {
    b->getSprite()->move(float(DISTANCE_BETWEEN_BIRDS_IN_QUEUE), 0);
  }

  return bird_to_return;
}

void Slingshot::receiveMessage(const std::string& id)
{
  if (id == "LOAD_NEXT_BIRD") // Sent from a bird when its been KIA
  {
    current_bird = getAndSetupBird();

    // If current_bird is null, there must be no more birds in the queue are therefore the game must be over
    if (!current_bird)
    {
      level->sendMessage("OUT_OF_BIRDS");
    }
  }
}

sf::Sprite* Slingshot::getCurrentBirdSprite()
{
  // If there is no bird, then trying to get its sprite will result in a segmentation fault
  if (!current_bird) return nullptr;

  return current_bird->getSprite();
}

bool Slingshot::getCurrentBirdLaunchedState() const
{
  return current_bird->getLaunched();
}

void Slingshot::useCurrentBirdSpecial()
{
  if (current_bird)
  {
    current_bird->special();
  }
}

int Slingshot::getNumberOfBirds() const
{
  return bird_queue.size();
}