#include "Game.h"
 
Game game;

Game::Game()
{
  running = 1;
}

void Game::Init()
{
  worldMap.Init();
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