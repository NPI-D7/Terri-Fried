#include <renderd7.hpp>

class Game : public RenderD7::Scene
{
    public:
    Game();
    void Draw(void) const override;
    void Logic(u32 hDown, u32 hHeld, u32 hUp, touchPosition touch) override;
    private:
    //Spritesheet
    static RenderD7::Sheet tx;
    //Sprites
    static RenderD7::Sprite egg;
    static RenderD7::Sprite coin;
    static RenderD7::Sprite lava;
    static RenderD7::Sprite logo;
    static RenderD7::Sprite platform;
    static RenderD7::Sprite scorebox;
    static RenderD7::Sprite splash_egg;

    int screenheight = 240;
    int screenwidth = 400;
    double timer = 0;
    double lavaY = screenheight - 32/2;
};
