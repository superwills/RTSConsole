#pragma once

#include "GameObject.h"

struct WorldMap;

struct Unit : public GameObject
{
  Unit();

  SMALL_RECT getRect() const;
  void Update( WorldMap* worldMap );

  virtual bool isAttackable();

  // Attack unit.
  void ReceiveAttack( GameObject& fromUnit );
};

