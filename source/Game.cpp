#include "Game.hpp"

Game::Game()
{
    //Load Spritesheet
    this->tx.Load("romfs:/gfx/tx.t3x");
    //Load Sprites
    this->egg.FromSheet(&tx, 0);
    this->coin.FromSheet(&tx, 1);
    this->lava.FromSheet(&tx, 2);
    this->logo.FromSheet(&tx, 3);
    this->platform.FromSheet(&tx, 4);
    this->scorebox.FromSheet(&tx, 5);
    this->splash_egg.FromSheet(&tx, 6);
    //Scale the Sprites
    this->egg.SetScale(0.5, 0.5);
    this->coin.SetScale(0.5, 0.5);
    this->lava.SetScale(0.5, 0.5);
    this->logo.SetScale(0.5, 0.5);
    this->platform.SetScale(0.5, 0.5);
    this->scorebox.SetScale(0.5, 0.5);
    this->splash_egg.SetScale(0.5, 0.5);

}

void Game::Draw(void) const
{
    RenderD7::OnScreen(Top);
    RenderD7::DrawRect(0, 0, this->screenwidth, this->screenheight, RenderD7::Color::Hex("#ECE2DE"));
    this->egg.Draw();
    this->lava.Draw();
}

void Game::Logic(u32 hDown, u32 hHeld, u32 hUp, touchPosition touch)
{
    this->lavaY = screenheight - 16 - sin(this->timer) * 5;
    this->timer += 0.05/2;
    this->lava.SetPos(0, lavaY);
}
