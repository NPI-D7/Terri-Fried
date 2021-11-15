#include <renderd7.hpp>

class Game : public RenderD7::Scene
{
    public:
    Game();
    void Draw(void) const override;
    void Logic(u32 hDown, u32 hHeld, u32 hUp, touchPosition touch) override;
    private:
    //Spritesheet
    inline RenderD7::Sheet tx;
    //Sprites
    inline RenderD7::Sprite egg;
    inline RenderD7::Sprite coin;
    inline RenderD7::Sprite lava;
    inline RenderD7::Sprite logo;
    inline RenderD7::Sprite platform;
    inline RenderD7::Sprite scorebox;
    inline RenderD7::Sprite splash_egg;

    inline int screenheight = 240;
    inline int screenwidth = 400;
    inline double timer = 0;
    inline double lavaY = screenheight - 32/2;
};
