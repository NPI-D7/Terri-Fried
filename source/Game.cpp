#include "Game.hpp"
#include "platform.hpp"
#include "player.hpp"
#include "sound.hpp"

const double pi = 3.1415926535897;
const double gravity = 1;
int velocityX;
int velocityY;

bool debugmode = false;

int spt;
std::string d_ver = "V1.0 ";
Platform platforms[5] = {{0}, {1}, {2}, {3}, {4}};
Player player(platforms[0].getX() + platforms[0].getWidth()/2 - (26/2)/2, platforms[0].getY() - player.getHeight(), 26/2, 32/2);
//Spritesheet
RenderD7::Sheet tx;
C2D_Font font;
//Sprites :)
/*Load Sprites
    egg.FromSheet(&tx, 0);
    coin.FromSheet(&tx, 1);
    lava.FromSheet(&tx, 2);
    logo.FromSheet(&tx, 3);
    platform.FromSheet(&tx, 4);
    scorebox.FromSheet(&tx, 5);
    splash_egg.FromSheet(&tx, 6);
*/

std::unique_ptr<sound> sfx_click = nullptr;
std::unique_ptr<sound> sfx_coin = nullptr;
std::unique_ptr<sound> sfx_die = nullptr;
std::unique_ptr<sound> sfx_launch = nullptr;
std::unique_ptr<sound> sfx_select = nullptr;
std::unique_ptr<sound> sfx_splash = nullptr;

int screenheight = 240;
int screenwidth = 400;
int mouseDownX = 0;
int mouseDownY = 0;
double timer = 0;
double lavaY = screenheight - 32/2;
bool firstTime = true;
int LoadHighScore() {
    FILE *scorefile = fopen("sdmc:/terri-fried-score.bin", "rb");
    
    if(!scorefile)
        return 0;
    
    int ret;
    fread(&ret, sizeof(int), 1, scorefile);
    fclose(scorefile);
    
    return ret;
}

void SaveHighScore(int val) {
    FILE *scorefile = fopen("sdmc:/terri-fried-score.bin", "wb");
    
    fwrite(&val, sizeof(int), 1, scorefile);
    fclose(scorefile);
}

int scoreInt = 0;
int highscoreInt = LoadHighScore();
char score[32] = "000";
char highscore[32];

bool titlescreen = true;
bool splashScreen = true;
bool playCoinFX = false;
bool g_ame = false;

void addScore(int amount) {
    scoreInt += amount;
    
    if (scoreInt < 10)
        sprintf(score, "00%d", scoreInt);
    else if (scoreInt < 100)
        sprintf(score, "0%d", scoreInt);
    else
        sprintf(score, "%d", scoreInt);
    
    if (scoreInt > highscoreInt && scoreInt < 1000) {
        highscoreInt = scoreInt;
        sprintf(highscore, "BEST: %d", highscoreInt);
    }
}

void resetScore() {
    scoreInt = 0;
    sprintf(score, "00%d", scoreInt);
    SaveHighScore(highscoreInt);
}

void resetGame() {
    resetScore();
    
    for (int i = 0; i < 5; i++)
        platforms[i] = Platform(i);
    
    player.setVelocity(0, 0);
    player.setX(platforms[0].getX() + platforms[0].getWidth()/2 - (26/2)/2);
    player.setY(platforms[0].getY() - player.getHeight());
}

void checkPlayerCollision() {
    bool onPlatform = false;
    
    for (int i = 0; i < 5; i++) {
        if (platforms[i].getHasCoin() && player.getX() + player.getWidth() - 3 > platforms[i].getCoinX() && player.getX() + 3 < platforms[i].getCoinX() + 24/2 && player.getY() + player.getHeight() - 3 > platforms[i].getCoinY() && player.getY() + 3 < platforms[i].getCoinY() + 24/2) {
            addScore(1);
            platforms[i].setHasCoin(false);
            playCoinFX = true;
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
    sprintf(highscore, "BEST: %d", highscoreInt);
    RenderD7::loadFont(font, "romfs:/font.bcfnt");
    sfx_click = std::make_unique<sound>("romfs:/click.wav", 1);
    sfx_coin = std::make_unique<sound>("romfs:/coin.wav", 2);
    sfx_die = std::make_unique<sound>("romfs:/die.wav", 3);
    sfx_launch = std::make_unique<sound>("romfs:/launch.wav", 4);
    sfx_select = std::make_unique<sound>("romfs:/select.wav", 5);
    sfx_splash = std::make_unique<sound>("romfs:/splash.wav", 6);
    sfx_splash->play();
}

Game::~Game()
{
    tx.Free();
}

void Game::Draw(void) const
{
    if (splashScreen)
    {
        RenderD7::OnScreen(Bottom);
        RenderD7::DrawRect(0, 0, screenwidth, screenheight, RenderD7::Color::Hex("#ECE2DE"));
        // RenderD7::DrawTextCentered(0, 220, 0.6f, RenderD7::Color::Hex("#000000"), "Press Start to Exit.", 320, 0, font);

        RenderD7::OnScreen(Top);
        RenderD7::DrawRect(0, 0, screenwidth, screenheight, RenderD7::Color::Hex("#ECE2DE"));
        RenderD7::DrawImageFromSheet(&tx, 6, 190, 104, 0.5, 0.5);
        RenderD7::DrawTextCentered(0, 120, 0.6f, RenderD7::Color::Hex("#000000"), "POLYMARS, NPI-D7", 400, 0, font);
    }
    if (titlescreen && spt>120)
    {
        RenderD7::OnScreen(Bottom);
        RenderD7::DrawRect(0, 0, screenwidth, screenheight, RenderD7::Color::Hex("#ECE2DE"));
        

        RenderD7::OnScreen(Top);
        RenderD7::DrawRect(0, 0, screenwidth, screenheight, RenderD7::Color::Hex("#ECE2DE"));
        RenderD7::DrawImageFromSheet(&tx, 3, 100, 75, 0.5, 0.5);
        RenderD7::DrawTextCentered(0, 115, 0.6f, RenderD7::Color::Hex("#000000"), highscore, 400, 0, font);
        RenderD7::DrawTextCentered(0, 130, 0.6f, RenderD7::Color::Hex("#000000"), "CLICK ANYWHERE TO BEGIN", 400, 0, font);
    }
    if (g_ame) {
        RenderD7::OnScreen(Bottom);
        RenderD7::DrawRect(0, 0, screenwidth, screenheight, RenderD7::Color::Hex("#ECE2DE"));
        RenderD7::DrawTextCentered(0, 220, 0.6f, RenderD7::Color::Hex("#000000"), "Press Start to Exit.", 320, 0, font);
        RenderD7::DrawText(5, 1, 0.6f, RenderD7::Color::Hex("#000000"), d_ver, 0, 0, font);
        if (! RenderD7::IsNdspInit()){
            RenderD7::DrawText(5, 30, 0.6f, RenderD7::Color::Hex("#000000"), "SoundEngine failed!/n<<sdmc:/3ds/dspfirm.cdc>> not found", 0, 0, font);
        }
        RenderD7::OnScreen(Top);
        RenderD7::DrawRect(0, 0, screenwidth, screenheight, RenderD7::Color::Hex("#ECE2DE"));
        RenderD7::DrawImageFromSheet(&tx, 0, player.getX(), player.getY(), 0.5, 0.5);
        for (int i = 0; i < 5; i++)
        {
            RenderD7::DrawImageFromSheet(&tx, 4, platforms[i].getX(), platforms[i].getY(), 0.5, 0.5);
            if (platforms[i].getHasCoin()) RenderD7::DrawImageFromSheet(&tx, 1, platforms[i].getCoinX(), platforms[i].getCoinY(), 0.5, 0.5);
        }
        RenderD7::DrawImageFromSheet(&tx, 2, 0, lavaY, 0.5, 0.5);
        
        if (hidKeysHeld() & KEY_TOUCH && player.isOnGround())
        {
            C2D_DrawLine(mouseDownX + (player.getX() - mouseDownX) + (player.getWidth()/2),
                    mouseDownY + (player.getY() - mouseDownY) + (player.getHeight()/2),
                    RenderD7::Color::Hex("#000000"),
                    d7_touch.px + (player.getX() - mouseDownX) + (player.getWidth()/2),
                    d7_touch.py + (player.getY() - mouseDownY) + (player.getHeight()/2),
                    RenderD7::Color::Hex("#000000"),
                    1,
                    1
                );
        }
        RenderD7::DrawImageFromSheet(&tx, 5, 10, 5, 0.5, 0.5);
        RenderD7::DrawText(17, 6, 1.1f, RenderD7::Color::Hex("#000000"), score, 0, 0, font);
        RenderD7::DrawText(10, 40, 0.7f, RenderD7::Color::Hex("#000000"), highscore, 0, 0, font);
    }
}

void Game::Logic(u32 hDown, u32 hHeld, u32 hUp, touchPosition touch)
{
    if (titlescreen)
    {
        if (splashScreen)
        {
             if (spt>120){splashScreen = false;}
        }
        spt +=1;
        
            if (hDown & KEY_TOUCH && spt>120)
            {
                sfx_select->play();
                g_ame = true;
                titlescreen = false;
            }
       
    }
    if (g_ame)
    {
        lavaY = screenheight - 16 - sin(timer) * 5;
        timer += 0.05/2;
        for (int i = 0; i < 5; i++) {
            platforms[i].updatePosition();
        }
        checkPlayerCollision();
        player.updatePosition();
        
        if (player.getY() > screenheight) {
            sfx_die->play();
            resetGame();
        }
        if ((hidKeysDown() & KEY_TOUCH && player.isOnGround()))
        {
            sfx_click->play();
            mouseDownX = touch.px;
            mouseDownY = touch.py;
        }

        if ((hidKeysHeld() & KEY_TOUCH && player.isOnGround()))
        {
            velocityX = touch.px - mouseDownX;
            velocityY = touch.py - mouseDownY;
        }
    
        if ((hidKeysUp() & KEY_TOUCH && player.isOnGround()))
        {
            if (firstTime)
            {
                firstTime = false;
            }
            else {
                sfx_launch->play();
                if(player.isOnPlatform()) player.setY(player.getY() - 1);
             
                player.setVelocity((double)velocityX*.16, (double)velocityY*.16);
            } 
        }
        
        if (playCoinFX) 
        {
            sfx_coin->play();
            playCoinFX = false;
        }
        if (hDown & KEY_START) RenderD7::ExitApp();
        if (debugmode){
        std::string dbgi = "DebugInfo: \nLavaY: ";
        dbgi += std::to_string(lavaY).substr(0, 3);
        dbgi += "\nVelocity: ";
        dbgi += std::to_string(velocityX);
        dbgi += ", ";
        dbgi += std::to_string(velocityY);
        dbgi += "\nTouchPos: ";
        dbgi += std::to_string(touch.px);
        dbgi += ", ";
        dbgi += std::to_string(touch.py);
        dbgi += "\nDownPos: ";
        dbgi += std::to_string(mouseDownX);
        dbgi += ", ";
        dbgi += std::to_string(mouseDownY);
        dbgi += "\nU: ";
        dbgi += std::to_string(hidKeysUp() ? 1 : 0);
        dbgi += " D: ";
        dbgi += std::to_string(hidKeysDown() ? 1 : 0);
        dbgi += " H: ";
        dbgi += std::to_string(hidKeysHeld() ? 1 : 0);
        RenderD7::OnScreen(Bottom);
        RenderD7::DrawText(5, 50, 0.6f, RenderD7::Color::Hex("#000000"), dbgi, 0, 0, font);
        }
    }
}
