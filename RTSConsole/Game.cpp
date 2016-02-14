#include "Game.h"
 
Game game;

Game::Game()
{
  running = 1;
}

void Game::Init()
{
  CenterConsoleWindow();
  worldMap.Init();
}

void Game::CenterConsoleWindow()
{
  // Center the console window.
  HWND hwnd = GetConsoleWindow();
  int screenWidth = GetSystemMetrics( SM_CXSCREEN ); // This is the width of the whole screen.
  RECT rect; // This gets the width/height of the console window.
  GetWindowRect( hwnd, &rect );
  int windowWidth = rect.right - rect.left;
  SetWindowPos( hwnd, 0, screenWidth/2 - windowWidth/2, 0, rect.right-rect.left, rect.bottom-rect.top, SWP_NOSIZE ); 
}

void Game::Update()
{
  if( GetAsyncKeyState( VK_RIGHT ) )
    worldMap.player.vel.x = worldMap.player.speed;
  if( GetAsyncKeyState( VK_LEFT ) )
    worldMap.player.vel.x = -worldMap.player.speed;
  if( GetAsyncKeyState( VK_UP ) )
    worldMap.player.vel.y = -worldMap.player.speed;
  if( GetAsyncKeyState( VK_DOWN ) )
    worldMap.player.vel.y = worldMap.player.speed;
  worldMap.Update();

  if( GetAsyncKeyState( VK_ESCAPE ) )
    running = 0;
}



void Game::Draw()
{
  // Draw the world map into the background, player, items & enemy
  worldMap.Draw();
}