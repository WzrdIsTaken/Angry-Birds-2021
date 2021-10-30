#pragma once

#include "LevelBase.h"

class Level1 : public LevelBase
{
 public:
  void start() override;
  void constructLevel() override;
  void restartLevel() override;
};