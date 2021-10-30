#pragma once

#include "../../Engine.h"

class MusicManager : public bcw::Scene
{
 public:
  void start() override;

  enum Songs { MENU, LEVEL };

  void playSong(Songs _song);

  void setVolume(float new_volume);
  float getVolume() const;

 private:
  sf::Music music;

  Songs song = MENU;

  const std::string menu_song_path = "Data/Music/MenuSong.ogg";
  const std::string level_song_path = "Data/Music/LevelSong.ogg";
  const std::string best_song_path = "Data/Music/BestSong.ogg";
};

// Get 'AL lib: (EE) alc_cleanup: 1 device not closed' when closing the program. Maybe find a solution? Doesn't seem to be a big issue atm though.