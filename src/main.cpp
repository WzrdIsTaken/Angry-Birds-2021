#include "Engine.h"

#include "Game/MainMenuScene.h"

int main()
{
  sf::RenderWindow window(sf::VideoMode(1080, 720), "Angry Birds", sf::Style::Titlebar | sf::Style::Close);
  window.setFramerateLimit(60);

  bcw::Engine engine(window, new MainMenuScene);
  sf::Clock clock;

  while (window.isOpen())
  {
    sf::Event event{};

    float dt = clock.restart().asSeconds();

    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        window.close();
      }
      if (event.type == sf::Event::MouseButtonPressed)
      {
        engine.mouseClicked();
      }
      else if (event.type == sf::Event::MouseButtonReleased)
      {
        engine.mouseReleased();
      }
      if (event.type == sf::Event::KeyPressed)
      {
        engine.keyPressed(event.key.code);
      }
    }

    engine.update(dt);
    window.clear(sf::Color::Black);

    engine.render();
    window.display();
  }

  return 0;
}

/*
 The aim for this project is not to have to edit the Engine scripts at all, just work within their limitations then never have to look at my awful code every again xD.
 Will I succeed? Find out next time!

 brb converting stuff to comply with coding standards...

 ok didn't succeed, but at least (so far...) the changes have only been minor
*/