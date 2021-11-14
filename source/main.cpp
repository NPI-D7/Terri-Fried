#include <renderd7.hpp>

int main()
{
    RenderD7::Init::Main();
    
    while(RenderD7::MainLoop())
    {
        if (d7_hDown & KEY_B) RenderD7::ExitApp();
        RenderD7::OnScreen(top);
        RenderD7::DrawRect(0, 0, 20, 20, C2D_Color32(255, 255 , 255, 255));
        C3D_FrameEnd(0);
    }

    RenderD7::Exit::Main();
    return 0;
}