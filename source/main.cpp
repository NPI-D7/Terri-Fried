#include <renderd7.hpp>
#include <time.h>

int main()
{
    RenderD7::Init::Main();
    srand(time(NULL));
    
    while(RenderD7::MainLoop())
    {
        if (d7_hDown & KEY_B) RenderD7::ExitApp();
        RenderD7::Scene::doDraw();
        RenderD7::Scene::doLogic(d7_hDown, d7_hHeld, d7_hUp, d7_touch);
        C3D_FrameEnd(0);
    }

    RenderD7::Exit::Main();
    return 0;
}
