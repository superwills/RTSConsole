#include "Unit.h"
#include "WorldMap.h"

Unit::Unit()
{
  symbol.Char.AsciiChar = 'U';
  symbol.Attributes = FOREGROUND_RED | FOREGROUND_INTENSITY;
}

SMALL_RECT Unit::getRect() const {
  // Check bounds of rectangle for rendering
  return {
    (short)pos.x, (short)pos.y,
    (short)pos.x+1, (short)pos.y+1 /*ltrb wnes*/
  };
}

void Unit::Update( WorldMap* worldMap )
{
  Vector2 proposedPos = pos + vel;
  if( !worldMap->Occupied( proposedPos ) ) {
    // erase unit in old position in character map
    worldMap->characterMap[ worldMap->li( pos ) ] = WorldMap::blank;
    pos = proposedPos;
  }
  vel = { 0, 0 }; // Clear old velocity (or multiply by value less than 1 to slow the player down)

  // Bake updated position into the backingMap
  worldMap->characterMap[ worldMap->li( pos ) ] = symbol;
}

bool Unit::isAttackable() { return true; }

// Attack unit.
void Unit::ReceiveAttack( GameObject& fromUnit )
{
  float damage = fromUnit.attackPower - defensePower;
  if( damage > 0 )
  {
    hp -= damage;

    if( hp < 0 ) {
      hp = 0;
      Die();
    }
  }
  else
  {
    // zero damage attack.
    info( "%s sent 0 damage to %s", fromUnit.name.c_str(), name.c_str() );
    PlaySound( TEXT( "clang.wav" ), NULL, SND_FILENAME | SND_ASYNC );
  }
}
