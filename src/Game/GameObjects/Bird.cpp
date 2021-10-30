#include "../../EngineMethods.h"

#include "Bird.h"

#include "Poof.h"

void Bird::setup(sf::Vector2f startPos, BirdTypes _birdType, bcw::Scene* _slingshot, sf::Vector2f initial_velocity)
{
  std::string bird_name;

  switch (_birdType)
  {
    case RED:
      bird_name = "Red";
      break;
    case CHUCK:
      bird_name = "Chuck";
      break;
    case BLUE:
      bird_name = "Blue";

      if (initial_velocity != sf::Vector2f(0,0))
      {
        velocity = initial_velocity;
        launched = true;
        used_special = true;
        clone = true;
      }
      break;
  }

  bcw::Renderer::renderSprite(&texture, &sprite, "Data/Images/OtherCoolSprites/" + bird_name + ".png", startPos.x, startPos.y, 0.05, 0.05);

  slingshot = _slingshot;
  birdType = _birdType;

  setTag("Bird");
  bcw::Physics::addCollidableItem(&sprite, this);
}

void Bird::launch(sf::Vector2f direction, float force)
{
  velocity = bcw::MoreMath::normalize(direction) * force * FORCE_MULTIPLIER;
  launched = true;
}

void Bird::special()
{
  if (used_special || !launched)
  {
    return;
  }

  switch (birdType)
  {
    default: // Up here because 'jump bypasses variable initialization'
      break;
    case CHUCK:
      velocity.x += CHUCK_BOOST_AMOUNT;
      break;
    case BLUE:
      Bird* top = bcw::SceneManagement::instanceScene(new Bird);
      top->setup(sprite.getPosition(), BirdTypes::BLUE, slingshot, sf::Vector2f(velocity.x, velocity.y + 50));

      Bird* bot = bcw::SceneManagement::instanceScene(new Bird);
      bot->setup(sprite.getPosition(), BirdTypes::BLUE, slingshot, sf::Vector2f(velocity.x, velocity.y - 50));
      break;
  }

  used_special = true;
}

void Bird::update(float dt)
{
  if (launched)
  {
    sprite.move(velocity * dt);

    if ((velocity == sf::Vector2f(0, 0) || sprite.getPosition().x > 1100 || sprite.getPosition().x < -20 || sprite.getPosition().y < -60) && !next_bird_loaded)
    {
      if (!clone)
      {
        next_bird_loaded = true;
        slingshot->sendMessage("LOAD_NEXT_BIRD");

        bcw::SceneManagement::instanceScene(new Poof)->setup(sprite.getPosition(), 2);
      }

      bcw::Renderer::derenderDrawable(&sprite);
      setActiveState(false);
    }

    if (sprite.getPosition().y < GROUND_HEIGHT)
    {
      velocity.y += MASS;
    }
    else
    {
      velocity.x -= MASS * DRAG;
      if (velocity.x < 0)
      {
        velocity.x = 0;
      }

      velocity.y = 0;
    }
  }
}

void Bird::onCollisionEnter(bcw::Scene* collision)
{
  // Sometimes this won't trigger if the bird is moving at high speed and hits a pig, though that's kinda like the real game,
  // so its a feature - not a bug!
  if (collision->getTag() == "Block" || collision->getTag() == "Pig")
  {
    velocity = sf::Vector2f(0, 0);
  }
}

sf::Sprite* Bird::getSprite()
{
  return &sprite;
}

bool Bird::getLaunched() const
{
  return launched;
}

// Maybe a better way to handle the collision with the floor / blocks. Currently works but doesn't look very nice.
// However, this isn't a priority.