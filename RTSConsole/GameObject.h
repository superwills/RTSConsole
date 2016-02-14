#pragma once

#include <stdio.h>
#include <Windows.h>

#include <string>
using namespace std;

#include "Util.h"
#include "Vector2.h"

struct GameObject
{
  enum Colors {
    FgRed = FOREGROUND_RED, FgGreen = FOREGROUND_GREEN, FgBlue = FOREGROUND_BLUE,
    FgLtGray = FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE, FgDkGray = FOREGROUND_INTENSITY,
    FgWhite= FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY,
    BgRed = BACKGROUND_RED, BgGreen = BACKGROUND_GREEN, BgBlue = BACKGROUND_BLUE,
    BgLtGray = BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE, BgDkGray = BACKGROUND_INTENSITY,
    BgWhite= BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|BACKGROUND_INTENSITY,
  };

  string name;

  Vector2 pos;
  Vector2 vel;
  float speed;
  float hp;
  float attackPower; // Attack Power
  float defensePower; // Defensive Power

  CHAR_INFO symbol;

  GameObject()
  {
    symbol = { 'i', FgDkGray };
  }

  virtual bool isAttackable() { return false; }
  virtual void ReceiveAttack( GameObject& otherObject ) { }
  virtual void Die() {
    info( "%s is dying", name.c_str() );
  }
};

