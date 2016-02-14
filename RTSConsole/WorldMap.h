#pragma once

#include <Windows.h>

#include <string>
#include <vector>
using namespace std;

#include "Item.h"
#include "Monster.h"
#include "Player.h"

struct Message
{
  string message;
  DWORD color;
  Message() : message( "" ), color( FOREGROUND_INTENSITY ) { }
  Message( string iMessage, DWORD iColor ) : message( iMessage ), color( iColor ) { }
};

struct WorldMap
{
  // This is the single, global only pointer to the actual console (the black output window).
  HANDLE consoleHandle; // The "handle" to the system console, used for final flush out
  // To prevent flicker, we will use an output buffer to blast
  // all the characters and their CHAR_INFO to the console in
  // one call (rather than many printf() or WriteConsole() calls)
  HANDLE screenBuffer;

  // We maintain 4 layers of boards for each of the map itself, characters in the map,
  // items in the map, and the rendered (combined) output.
  vector< CHAR_INFO > baseMap, characterMap, itemMap, outputMap; // baseMap + character positions, item positions, output
  
  COORD size; // w/h of the console buffer map
  SMALL_RECT readRect, writeRect;

  Player player; // A single Unit object for the player's avatar
  vector< Monster > enemies; // A vector (simple array) of Units for the Enemies
  vector< Item > items;

  vector< Message > messages; // A queue of messages to show the player (space to advance)
  vector< CHAR_INFO > messageBuffer;
  COORD messageBufferSize;

  // Mapping that tells if a character is passible or not.
  map<char, bool> IsPassible;

  inline int li( int row, int col ) {
    return col + row*size.X; // col + row*[cols in map]
  }
  inline int li( COORD pos ) {
    return li( pos.Y, pos.X );
  }
  inline int li( Vector2 pos ) {
    return li( (int)pos.y, (int)pos.x );
  }

  WorldMap();

  // Initializes the map
  void Init();

  // Action happening in the map.
  void Update();

  // Flushes the world map from the baseMap to the ScreenBuffer.
  void Draw();

  // Puts the screen buffer out to the console.
  void Flush();

  void Log( string msg, DWORD color );

  bool Occupied( Vector2 pos );

  bool Occupied( COORD pos );
};

