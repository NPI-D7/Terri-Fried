#include <renderd7.hpp>
#include <time.h>

#include "Game.hpp"

int main()
{
    RenderD7::Init::Main("Terri-Fried");
    RenderD7::Init::NdspFirm(true);
    srand(time(NULL));
    RenderD7::Scene::Load(std::make_unique<Game>());
    while(RenderD7::MainLoop())
    {
        if (d7_hDown & KEY_B) RenderD7::ExitApp();
        C3D_FrameEnd(0);
    }
    RenderD7::Exit::NdspFirm();
    RenderD7::Exit::Main();
    return 0;
}
