#include <renderd7.hpp>

class Game : public RenderD7::Scene
{
    public:
    Game();
    void Draw(void) const override;
    void Logic(u32 hDown, u32 hHeld, u32 hUp, touchPosition touch) override;
    private:
    
};
