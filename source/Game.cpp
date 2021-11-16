#include "Game.hpp"
#include "platform.hpp"
#include "player.hpp"

const double pi = 3.1415926535897;
const int gravity = 1;

Platform platforms[5] = {{0}, {1}, {2}, {3}, {4}};
Player player(platforms[0].getX() + platforms[0].getWidth()/2 - (26/2)/2, platforms[0].getY() - player.getHeight(), 26/2, 32/2);
//Spritesheet
RenderD7::Sheet tx;
//Sprites
/*Load Sprites
    egg.FromSheet(&tx, 0);
    coin.FromSheet(&tx, 1);
    lava.FromSheet(&tx, 2);
    logo.FromSheet(&tx, 3);
    platform.FromSheet(&tx, 4);
    scorebox.FromSheet(&tx, 5);
    splash_egg.FromSheet(&tx, 6);
*/
int screenheight = 240;
int screenwidth = 400;
double timer = 0;
double lavaY = screenheight - 32/2;

void checkPlayerCollision() {
    bool onPlatform = false;
    
    for (int i = 0; i < 5; i++) {
        if (platforms[i].getHasCoin() && player.getX() + player.getWidth() - 3 > platforms[i].getCoinX() && player.getX() + 3 < platforms[i].getCoinX() + 24/2 && player.getY() + player.getHeight() - 3 > platforms[i].getCoinY() && player.getY() + 3 < platforms[i].getCoinY() + 24/2) {
            //addScore(1);
            platforms[i].setHasCoin(false);
            //playCoinFX = true;
        }
        
        if (player.getX() + 1 < platforms[i].getX() + platforms[i].getWidth() && player.getX() + player.getWidth() > platforms[i].getX() && player.getY() + player.getHeight() >= platforms[i].getY() && player.getY() < platforms[i].getY() + platforms[i].getHeight()) {
            if (player.getY() > platforms[i].getY() + platforms[i].getHeight()/2) {
                player.setVelocity(player.getVelocity().x, 5);
            } 
            else if (player.getY() + player.getHeight() <  platforms[i].getY() + platforms[i].getHeight()) {    
                onPlatform = true;
                player.setY(platforms[i].getY() - player.getHeight());
                player.setY(player.getY() + 1);
            }
        }
    }
    player.setOnPlatform(onPlatform);
}

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
    RenderD7::DrawImageFromSheet(&tx, 0, player.getX(), player.getY(), 0.5, 0.5);
    for (int i = 0; i < 5; i++)
    {
        RenderD7::DrawImageFromSheet(&tx, 4, platforms[i].getX(), platforms[i].getY(), 0.5, 0.5);
        if (platforms[i].getHasCoin()) RenderD7::DrawImageFromSheet(&tx, 1, platforms[i].getCoinX(), platforms[i].getCoinY(), 0.5, 0.5);
    }
    RenderD7::DrawImageFromSheet(&tx, 2, 0, lavaY, 0.5, 0.5);
    //RenderD7::DrawText(5, lavaY, 0.7f, RenderD7::Color::Hex("#FFFFFF"), "Test");
}

void Game::Logic(u32 hDown, u32 hHeld, u32 hUp, touchPosition touch)
{
    lavaY = screenheight - 16 - sin(timer) * 5;
    timer += 0.05/2;
    checkPlayerCollision();
    player.updatePosition();
    for (int i = 0; i < 5; i++) {
        platforms[i].updatePosition();
    }
}
