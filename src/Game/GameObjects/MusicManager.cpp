#include "MusicManager.h"

void MusicManager::start()
{
  setDontDestroyOnLoad(true);
  setTag("MusicManager");

  playSong(MENU);
  music.setLoop(true);
}

void MusicManager::playSong(MusicManager::Songs _song)
{
  song = _song;
  music.stop();

  switch (song)
  {
    case MENU:
      if (rand()%1000 == 42)
      {
        music.openFromFile(best_song_path);
        break;
      }

      music.openFromFile(menu_song_path);
      break;
    case LEVEL:
      music.openFromFile(level_song_path);
      break;
  }

  music.play();
}

void MusicManager::setVolume(float new_volume)
{
  music.setVolume(new_volume);
}

float MusicManager::getVolume() const
{
  return music.getVolume();
}