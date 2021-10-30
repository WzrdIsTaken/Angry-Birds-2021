#include <fstream>

#include "../../EngineMethods.h"

#include "LevelBase.h"
#include "../LevelSelectScene.h"

#include "../GameObjects/MusicManager.h"

void LevelBase::start()
{
  bcw::Renderer::renderSprite(&pause_button_texture, &pause_button, "Data/Images/UI/PauseButton.png", 10, 10);
  bcw::Renderer::renderText(&font, &score_text, "Data/Fonts/angrybirds-regular.ttf", "anyone reading this?", 40, sf::Color::White);

  updateScore(0);
  constructLevel();
}

void LevelBase::update(float dt)
{
  if (holding)
  {
    slingshot->moveBird(sf::Mouse::getPosition());
  }
}

void LevelBase::checkMousePressInput(sf::Vector2i click)
{
  // Game stuff (annoying it has to be here, but this is easier than fixing the bug in the wrapper xD)
  slingshot->useCurrentBirdSpecial();

  if (bcw::UserInput::checkClick(click, slingshot->getCurrentBirdSprite()) && !slingshot->getCurrentBirdLaunchedState())
  {
    holding = true;
  }

  // UI Stuff
  if (!game_over && (bcw::UserInput::checkClick(click, &pause_button) || bcw::UserInput::checkClick(click, &resume_text)))
  {
    bcw::SceneManagement::setPauseState(!bcw::SceneManagement::getPauseState());

    if (bcw::SceneManagement::getPauseState())
    {
      bcw::Renderer::renderText(&font, &pause_text, "Paused", 75, sf::Color::White, INFINITY, 225);
      bcw::Renderer::renderText(&font, &resume_text, "Resume", 25, sf::Color::White, INFINITY,350);
      bcw::Renderer::renderText(&font, &restart_text, "Restart", 25, sf::Color::White, INFINITY,400);
      bcw::Renderer::renderText(&font, &exit_text, "Exit", 25, sf::Color::White, INFINITY,450);

      pause_button.setColor(disabledColour);
    }
    else
    {
      bcw::Renderer::derenderDrawable(&pause_text);
      bcw::Renderer::derenderDrawable(&resume_text);
      bcw::Renderer::derenderDrawable(&restart_text);
      bcw::Renderer::derenderDrawable(&exit_text);

      pause_button.setColor(sf::Color::White);
    }
  }
  else if (bcw::UserInput::checkClick(click, &restart_text))
  {
    bcw::SceneManagement::setPauseState(false);
    restartLevel();
  }
  else if (bcw::UserInput::checkClick(click, &exit_text))
  {
    dynamic_cast<MusicManager*>(bcw::SceneManagement::findScene("MusicManager"))->playSong(MusicManager::Songs::MENU);
    bcw::SceneManagement::setPauseState(false);
    bcw::SceneManagement::changeScene(new LevelSelectScene);
  }
}

void LevelBase::checkMouseReleaseInput(sf::Vector2i click)
{
  if (holding)
  {
    holding = false;
    slingshot->launch();
  }
}

void LevelBase::receiveMessage(const std::string& id)
{
  if (id == "OUT_OF_BIRDS" && !game_over) // Sent from the slingshot
  {
    gameOver();
  }
  else if (id == "PIG_HIT") // Sent from the pigs
  {
    pig_count--;
    updateScore(100);

    if (pig_count == 0 && !game_over)
    {
      updateScore(slingshot->getNumberOfBirds() * 200);
      gameOver();
    }
  }
}

void LevelBase::updateScore(int increase)
{
  score += increase;
  bcw::Renderer::updateText(&score_text, std::to_string(score));

  // Make the text go from right to left
  score_text.setPosition(1070 - score_text.getLocalBounds().width, 10);
}

void LevelBase::gameOver()
{
  game_over = true;

  if (pig_count == 0)
  {
    const std::string file_name = "Highscores.txt";
    std::vector<std::string> scores;
    std::ifstream file_stream;
    file_stream.open(file_name);

    std::string line;
    while (std::getline(file_stream, line))
    {
      scores.push_back(line);
    }
    file_stream.close();

    if (std::stoi(scores[level_number - 1]) < score)
    {
      scores[level_number - 1] = std::to_string(score);

      std::ofstream output_file(file_name);
      std::ostream_iterator<std::string> output_iterator(output_file, "\n");
      std::copy(scores.begin(), scores.end(), output_iterator);
    }
  }

  bcw::Renderer::derenderDrawable(&score_text);
  bcw::Renderer::derenderDrawable(&pause_button);

  bcw::Renderer::renderText(&font, &pause_text, pig_count == 0 ? "You Win!" : "You Lose!", 75, sf::Color::White, INFINITY, 225);
  bcw::Renderer::renderText(&font, &resume_text, "Score: " + std::to_string(score), 25, sf::Color::White, INFINITY,350);
  bcw::Renderer::renderText(&font, &restart_text, "Play Again", 25, sf::Color::White, INFINITY,400);
  bcw::Renderer::renderText(&font, &exit_text, "Return To Menu", 25, sf::Color::White, INFINITY,450);
}