#include "../EngineMethods.h"

#include "MainMenuScene.h"
#include "LevelSelectScene.h"

#include "iostream"

void MainMenuScene::start()
{
  bcw::Renderer::renderSprite(&background_texture, &background_sprite, "Data/Images/MenuBackground.png");
  bcw::Renderer::renderSprite(&sound_fx_button_texture, &sound_fx_button, "Data/Images/UI/SoundFxButton.png", 10, 630, 0.75, 0.75);
  bcw::Renderer::renderSprite(&music_button_texture, &music_button, "Data/Images/UI/MusicButton.png", 10, 675, 0.75, 0.75);

  bcw::Renderer::renderText(&font, &title_text, "Data/Fonts/angrybirds-regular.ttf", "Angry Birds", 100, sf::Color::White, INFINITY, 100);
  bcw::Renderer::renderText(&font, &play_text, "Play", 50, sf::Color::White, INFINITY, 300);
  bcw::Renderer::renderText(&font, &exit_text, "Exit", 25, sf::Color::White, INFINITY, 375);

  Scene* _musicManager = bcw::SceneManagement::findScene("MusicManager");
  if (!_musicManager)
  {
    musicManager = bcw::SceneManagement::instanceScene(new MusicManager);
  }
  else
  {
    musicManager = dynamic_cast<MusicManager*>(_musicManager);
    music_button.setColor(musicManager->getVolume() == 0 ? disabledColour : sf::Color::White);
  }
}

void MainMenuScene::checkMousePressInput(sf::Vector2i click)
{
  if (bcw::UserInput::checkClick(click, &play_text))
  {
    bcw::SceneManagement::changeScene(new LevelSelectScene);
  }
  else if (bcw::UserInput::checkClick(click, &exit_text))
  {
    bcw::Renderer::window->close();
  }

  else if (bcw::UserInput::checkClick(click, &sound_fx_button))
  {
    sound_fx_button.setColor(sound_fx_button.getColor() == sf::Color::White ? disabledColour : sf::Color::White);

    std::cout << "Sound effects are not currently implemented because I need to move on to other assignments and audio is not on the mark scheme. "
                 "If there is time, I may come back and add some.\n" << std::endl;

    // Todo: sound fx system (same way as music) | https://www.sfml-dev.org/tutorials/2.5/audio-sounds.php
  }
  else if (bcw::UserInput::checkClick(click, &music_button))
  {
    music_button.setColor(music_button.getColor() == sf::Color::White ? disabledColour : sf::Color::White);
    musicManager->setVolume(musicManager->getVolume() == 0 ? 100 : 0);
  }
}