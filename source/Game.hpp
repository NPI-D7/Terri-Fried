#include <renderd7.hpp>

class Game : public RenderD7::Scene
{
    public:
    Game();
    void Draw(void) const override;
    void Logic(u32 hDown, u32 hHeld, u32 hUp, touchPosition touch) override;
    private:
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
};
