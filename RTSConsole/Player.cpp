#include "Player.h"

const char Player::Character = 'P';

Player::Player()
{
  symbol.Attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
  symbol.Char.AsciiChar = Character;

  speed = 0.25;
}

