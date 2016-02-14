#pragma once

#include <Windows.h>

#include "WorldMap.h"
 
struct Game
{
  WorldMap worldMap; // The world's map object, containing the map, player, and enemies
  bool running;
  Game();
  void Init();
  void Update();
  void Draw();

};

extern Game game;