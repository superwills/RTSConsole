#include "Monster.h"

map< Monster::MonsterType, char > Monster::Characters = {
  { Knight, 'K' },
  { Bishop, 'B' },
  { Rook, 'R' },
  { Queen, 'Q' },
  { King, 'I' },
};
