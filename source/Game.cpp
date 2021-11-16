#include "Game.hpp"

//Spritesheet
    RenderD7::Sheet tx;
    //Sprites
    RenderD7::Sprite egg;
    RenderD7::Sprite coin;
    RenderD7::Sprite lava;
    RenderD7::Sprite logo;
    RenderD7::Sprite platform;
    RenderD7::Sprite scorebox;
    RenderD7::Sprite splash_egg;

    int screenheight = 240;
    int screenwidth = 400;
    double timer = 0;
    double lavaY = screenheight - 32/2;
Game::Game()
{
    //Load Spritesheet
    tx.Load("romfs:/gfx/tx.t3x");
    //Load Sprites
    egg.FromSheet(&tx, 0);
    coin.FromSheet(&tx, 1);
    lava.FromSheet(&tx, 2);
    logo.FromSheet(&tx, 3);
    platform.FromSheet(&tx, 4);
    scorebox.FromSheet(&tx, 5);
    splash_egg.FromSheet(&tx, 6);
    //Scale the Sprites
    egg.SetScale(0.5, 0.5);
    coin.SetScale(0.5, 0.5);
    lava.SetScale(0.5, 0.5);
    logo.SetScale(0.5, 0.5);
    platform.SetScale(0.5, 0.5);
    scorebox.SetScale(0.5, 0.5);
    splash_egg.SetScale(0.5, 0.5);

}

void Game::Draw(void) const
{
    RenderD7::OnScreen(Bottom);
    RenderD7::DrawRect(0, 0, screenwidth, screenheight, RenderD7::Color::Hex("#ECE2DE"));
    RenderD7::OnScreen(Top);
    egg.Draw();
    lava.Draw();
    RenderD7::DrawText(5, lavaY, 0.7f, RenderD7::Color::Hex("#FFFFFF"), "Terri-Fried->Game");
}

void Game::Logic(u32 hDown, u32 hHeld, u32 hUp, touchPosition touch)
{
    lavaY = screenheight - 16 - sin(timer) * 5;
    timer += 0.05/2;
    lava.SetPos(0, lavaY);
}
