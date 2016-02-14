#include <stdio.h>
#include <Windows.h>
#include <stdarg.h>

#include <string>
#include <vector>
#include <map>
using namespace std;

#include "Game.h"
#include "GameObject.h"
#include "Item.h"
#include "Monster.h"
#include "Player.h"
#include "Unit.h"
#include "Util.h"
#include "Vector2.h"
#include "WorldMap.h"

// Library dependency for PlaySound()
#pragma comment( lib, "winmm.lib" )

int main()
{
  game.Init(); // Game.h defines this extern variable, and Game.cpp declares it.
  // Any file including Game.h then has use of this same superglobal Game instance.
  
  while( game.running )
  {
    game.Update();
    game.Draw();
  };
}