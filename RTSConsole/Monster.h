#pragma once

#include <map>
using namespace std;

#include "Unit.h"

struct Monster : public Unit
{
  enum MonsterType {
    Knight, Bishop, Rook, Queen, King, Fish, Penguin, Black
  };
  static map< MonsterType, char > Characters;
  MonsterType monsterType;

  Monster()
  {
    monsterType = Knight;
  }

  char getCharacter() { return Characters[ monsterType ]; }
};


