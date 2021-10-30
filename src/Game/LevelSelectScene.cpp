#include <fstream>

#include "../EngineMethods.h"

#include "LevelSelectScene.h"
#include "MainMenuScene.h"

#include "Levels/Level1.h"
#include "Levels/Level2.h"
#include "Levels/Level3.h"

void LevelSelectScene::start()
{
  bcw::Renderer::renderSprite(&background_texture, &background_sprite, "Data/Images/MenuBackground.png");
  bcw::Renderer::renderSprite(&back_button_texture, &back_button, "Data/Images/UI/MenuBackButton.png", 10, 10);

  bcw::Renderer::renderText(&font, &title_text, "Data/Fonts/angrybirds-regular.ttf", "Level Select", 100, sf::Color::White, INFINITY, 100);

  std::vector<std::string> scores = readFile();

  for (int i = 0; i < number_of_levels; i++)
  {
    bcw::Renderer::renderSprite(&level_button_textures[i], &level_buttons[i], "Data/Images/UI/Level" + std::to_string(i + 1) + "Button.png",
                                float(295 + (200 * i)), 300);
    bcw::Renderer::renderText(&font, &level_text[i], "Score: " + scores[i], 20, sf::Color::White, float(298 + (200 * i)), 370);
  }
}

void LevelSelectScene::checkMousePressInput(sf::Vector2i click)
{
  if (bcw::UserInput::checkClick(click, &back_button))
  {
    bcw::SceneManagement::changeScene(new MainMenuScene);
  }
  else
  {
    for (int i = 0; i < number_of_levels; i++)
    {
      if (bcw::UserInput::checkClick(click, &level_buttons[i]))
      {
        switch (i + 1)
        {
          case 1:
            bcw::SceneManagement::changeScene(new Level1);
            break;
          case 2:
            bcw::SceneManagement::changeScene(new Level2);
            break;
          case 3:
            bcw::SceneManagement::changeScene(new Level3);
            break;
        }

        dynamic_cast<MusicManager*>(bcw::SceneManagement::findScene("MusicManager"))->playSong(MusicManager::Songs::LEVEL);

        break;
      }
    }
  }
}

std::vector<std::string> LevelSelectScene::readFile()
{
  const std::string file_name = "Highscores.txt";
  std::vector<std::string> return_vector;

  if (std::ifstream(file_name))
  {
    std::ifstream file_stream;
    file_stream.open(file_name);

    std::string line;
    while (std::getline(file_stream, line))
    {
      return_vector.push_back(line);
    }

    file_stream.close();
  }
  else
  {
    std::ofstream out_file(file_name);
    out_file << "000\n000\n000" << std::endl;
    out_file.close();

    return_vector = {"000", "000", "000"};
  }

  return return_vector;
}