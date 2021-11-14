#include <renderd7.hpp>

RenderD7::Sheet tx;
RenderD7::Sprite splash;
int main()
{
    RenderD7::Init::Main();
    tx.Load("romfs:/gfx/tx.t3x");
    splash.FromSheet(&tx, 3);
    while(RenderD7::MainLoop())
    {
        if (d7_hDown & KEY_B) RenderD7::ExitApp();
        RenderD7::OnScreen(Top);
        
        RenderD7::DrawRect(0, 0, 20, 20, C2D_Color32(255, 255 , 255, 255));
        splash.Draw();
        C3D_FrameEnd(0);
    }

    RenderD7::Exit::Main();
    return 0;
}
