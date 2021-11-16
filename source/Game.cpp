#include "Game.hpp"

//Spritesheet
RenderD7::Sheet tx;
//Sprites
/"Load Sprites
    egg.FromSheet(&tx, 0);
    coin.FromSheet(&tx, 1);
    lava.FromSheet(&tx, 2);
    logo.FromSheet(&tx, 3);
    platform.FromSheet(&tx, 4);
    scorebox.FromSheet(&tx, 5);
    splash_egg.FromSheet(&tx, 6);*/
int screenheight = 240;
int screenwidth = 400;
double timer = 0;
double lavaY = screenheight - 32/2;
Game::Game()
{
    //Load Spritesheet
    tx.Load("romfs:/gfx/tx.t3x");
}

void Game::Draw(void) const
{
    RenderD7::OnScreen(Bottom);
    RenderD7::DrawRect(0, 0, screenwidth, screenheight, RenderD7::Color::Hex("#ECE2DE"));
    RenderD7::OnScreen(Top);
    RenderD7::DrawRect(0, 0, screenwidth, screenheight, RenderD7::Color::Hex("#ECE2DE"));
    RenderD7::DrawImageFromSheet(&tx, 0, 0, 0, 0.5, 0.5);
    RenderD7::DrawImageFromSheet(&tx, 2, 0, lavaY, 0.5, 0.5);
    //RenderD7::DrawText(5, lavaY, 0.7f, RenderD7::Color::Hex("#FFFFFF"), "Test");
}

void Game::Logic(u32 hDown, u32 hHeld, u32 hUp, touchPosition touch)
{
    lavaY = screenheight - 16 - sin(timer) * 5;
    timer += 0.05/2;
    lava.SetPos(0, lavaY);
}
