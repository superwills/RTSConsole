#include "WorldMap.h"

CHAR_INFO WorldMap::floor = { '.', FOREGROUND_GREEN }, WorldMap::blank = {' ', 0}, WorldMap::horizontalWall = { '-', FOREGROUND_BLUE },
  WorldMap::verticalWall = { '|', FOREGROUND_BLUE }, WorldMap::corner = { '+', FOREGROUND_BLUE };
  
WorldMap::WorldMap()
{
  // Initialize the console handle
  consoleHandle = GetStdHandle( STD_OUTPUT_HANDLE );
  screenBuffer = CreateConsoleScreenBuffer( GENERIC_WRITE | GENERIC_READ,
    FILE_SHARE_READ | FILE_SHARE_WRITE, 0, CONSOLE_TEXTMODE_BUFFER, 0 );
  SetConsoleActiveScreenBuffer( screenBuffer );
}

// Initializes the map
void WorldMap::Init()
{
  // Initialize the baseMap.
  // Ascii-box drawing character string baseMap
  size = { 40, 20 };
  
  // Mark the floor as passible.
  IsPassible[ floor.Char.AsciiChar ] = 1;

  baseMap.resize( size.X * size.Y, floor );
  characterMap.resize( size.X * size.Y, blank );
  itemMap.resize( size.X * size.Y, blank );
  outputMap.resize( size.X * size.Y, blank );

  // Corners.
  baseMap[ 0 ] = baseMap[ li( 0, size.X - 1 ) ] =
    baseMap[ li( size.Y - 1, 0 ) ] = baseMap[ li( size.Y - 1, size.X - 1 ) ] = corner;
  for( int i = 1; i < size.X - 1; i++ )
    baseMap[ i ] = baseMap[ li( size.Y - 1, i ) ] = horizontalWall;
  for( int i = 1; i < size.Y - 1; i++ )
    baseMap[ li( i, 0 ) ] = baseMap[ li( i, size.X - 1 ) ] = verticalWall;
  // Go inside the baseMap and fill with .
  for( int row = 1; row < size.Y - 1; row++ )
    for( int col = 1; col < size.X - 1; col++ )
      baseMap[ li( row, col ) ] = floor;

  // The output map starts as the baseMap
  outputMap = baseMap;

  // Try and set a unicode codepage into the console
  player.pos = Vector2( 2, 2 );

}

// Action happening in the map.
void WorldMap::Update()
{
  // We update the player & monster positions,
  player.Update( this );
  for( int i = 0; i < enemies.size(); i++ )
    enemies[i].Update( this );

  // then re-form the map
  outputMap = baseMap;

  // render messages
  if( messages.size() )
  {
    Message msg = *messages.begin();
    COORD textPos = { 2, size.Y + 1 };
    SetConsoleCursorPosition( screenBuffer, textPos );
    
    SMALL_RECT writeRegion = { 0, size.Y, (short)msg.message.size(), size.Y+1 }; //ltrb
    WriteConsoleOutput( screenBuffer, &messageBuffer[0], messageBufferSize, {0,0}, &writeRegion );
  }
}

// Flushes the world map from the Board to the ScreenBuffer.
void WorldMap::Draw()
{
  outputMap = baseMap;

  // Write the output map from baseMap + all other map layers
  for( int i = 0; i < outputMap.size(); i++ )
  {
    if( !IsBlank( characterMap[i] ) )
      outputMap[i] = characterMap[i];
    if( !IsBlank( itemMap[i] ) )
      outputMap[i] = itemMap[i];
  }

  // Finally, we flush our buffers out to the actual console window.
  Flush();
}

// Puts the screen buffer out to the console.
void WorldMap::Flush()
{
  // You don't need newlines in the output, the writeRegion
  // determines rectangle into which the linear array is written
  SMALL_RECT writeRegion = { 0, 0, size.X, size.Y }; //ltrb
  WriteConsoleOutput( screenBuffer, &outputMap[0], size, {0,0}, &writeRegion );
}

void WorldMap::Log( string msg, DWORD color )
{
  messages.push_back( { msg, color } );
}

bool WorldMap::Occupied( Vector2 pos )
{
  COORD coordinatePosition = { (short)pos.x, (short)pos.y };
  return Occupied( coordinatePosition );
}

bool WorldMap::Occupied( COORD pos )
{
  // out-of-bounds is also considered "occupied" (by walls etc)
  if( pos.X < 0 || pos.X >= size.X )  return 1; // L & R
  if( pos.Y < 0 || pos.Y >= size.Y )  return 1; // T & B

  // check against any walls or characters in the buffer
  char c = outputMap[ li( pos ) ].Char.AsciiChar;

  return !IsPassible[ c ];
}
