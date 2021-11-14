#pragma once
#include <3ds.h>
#include <citro2d.h>
#include <citro3d.h>
#include <memory>
#include <stack>
#include <string>
#include <functional>
#include <vector>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <cstring>
#include <sys/stat.h>
#include <algorithm>
#include <iostream>
#include "external/lodepng.h"
#include "external/fs.h"
#include <codecvt>
#include "lang.hpp"
#include "parameter.hpp"
#include "thread.hpp"
#include "ini.hpp"
#include "stringtool.hpp"

#define RENDERD7VSTRING "0.6.10"
#define CHANGELOG "0.6.10: rewrite Threadsystem, Improve framerate/n0.6.02: Fix Code in lang.hpp\nadd Draw Text Left Function.\nadd changelog\n0.6.01: add Threading system."
#define DEFAULT_CENTER 0.5f

extern C3D_RenderTarget* Top;
extern C3D_RenderTarget* TopRight;
extern C3D_RenderTarget* Bottom;

extern u32 d7_hDown;
extern u32 d7_hHeld;
extern u32 d7_hUp;
extern touchPosition d7_touch;

extern std::string dspststus;

/// RenderD7
namespace RenderD7
{
    enum kbd{
         SWKBD,
         BKBD
    };
    enum kbd_type
    {
         NUMPAD,
         STANDARD
    };
    /// Set current RenderScreen
    /// \param target The RenderTarget Top, Bottom
    void OnScreen(C3D_RenderTarget *target);
    /** The Spritesheet Class */
    class Sheet
    {
        public:
        /// Construct sheet
        Sheet();
        // Deconstruct sheet
        ~Sheet();
        /// Load a Sritesheet
        /// path: Path to the Spritesheet (.t3x)
        Result Load(const char *path);
        /// Unload the Spritesheet
        void Free();
        // The Spritesheet
        C2D_SpriteSheet spritesheet;
    };
    /// Image Class
    class Image
    {
        public:
        /// Load Image from Png
        /// path: path to png file
        void LoadPng(const std::string path);
        /// Load the Image from buffer
        /// buffer: the frame buffer
        void LoadPFromBuffer(const std::vector<u8> &buffer);
        /// Draw the Image directly
        /// \param x The x position
        /// \param y the y position
        /// \param scaleX x scale from 0.0 to 1.0
        /// \param scaleY y scale from 0.0 to 1.0
        bool Draw(float x, float y, float scaleX = 1.0f, float scaleY = 1.0f);
        /// \brief Get The Image
        /// \return C2D_Image
        C2D_Image Get(){return this->img;}
        /// \img this is the C2D_Image
        C2D_Image img;
        /// \loadet whether the image is loadet or not
        bool loadet = false;
    };
    /// Sprite Class
    class Sprite
    {
        public:
        /// \brief Construct Sprite
        Sprite();
        ~Sprite();
        void FromSheet(RenderD7::Sheet *sheet, size_t index);
        void FromImage(RenderD7::Image *img);
        bool Draw();
        void SetCenter(float x, float y);
        void SetPos(float x, float y);
        void SetScale(float x, float y);
        void SetRotation(float rotation);
        void Rotate(float speed);
        float getWidth();
        float getHeigh();
        float getPosX();
        float getPosY();
        private:
        C2D_ImageTint tint;
        C2D_Sprite sprite;
    };

    class Scene {
    public:
        static std::stack<std::unique_ptr<Scene>> scenes;
    	virtual ~Scene() {}
    	virtual void Logic(u32 hDown, u32 hHeld, u32 hUp, touchPosition touch) = 0;
    	virtual void Draw() const = 0;
        //virtual void Ovl() const = 0;
        static void Load(std::unique_ptr<Scene> scene);
        static void Back();
        static void doDraw();
        static void doLogic(u32 hDown, u32 hHeld, u32 hUp, touchPosition touch);
        //static void HandleOvl();
    };

    namespace Color
    {
        u32 Hex(const std::string color, u8 a = 255);
    }
    void DrawMetrikOvl();
    bool DrawImageFromSheet(RenderD7::Sheet* sheet, size_t index, float x, float y, float scaleX = 1.0, float scaleY = 1.0);
    namespace Error
    {
        void DisplayError(std::string toptext, std::string errortext);
        void DisplayFatalError(std::string toptext, std::string errortext);
    }
    namespace Init
    {
        Result Main();
        void NdspFirm(bool useit = false);
    }
    namespace Exit
    {
        void Main();
        void NdspFirm();
    }
    namespace Msg
    {
        void Display(std::string titletxt, std::string subtext, C3D_RenderTarget *target);
        void DisplayWithProgress(std::string titletext, std::string subtext, float current, float total, u32 prgbarcolor);
    }
    
    namespace Convert
    {
        inline float StringtoFloat(std::string inp){return std::atof(inp.c_str());}
        inline bool FloatToBool(float inp){if(inp == 1)return true; else return false;}
    }
    namespace FS
    {
        bool FileExist(const std::string& path);
    }
    bool IsNdspInit();
    void SetupLog(void);
    std::string GetFramerate();
    bool MainLoop();
    void ExitApp();
    
    void ClearTextBufs(void);
   
    bool DrawRect(float x, float y, float w, float h, u32 color);
    bool DrawPx(float x, float y, u32 color);
    void DrawTextCentered(float x, float y, float size, u32 color, std::string Text, int maxWidth = 0, int maxHeight = 0, C2D_Font fnt = nullptr);
	void DrawText(float x, float y, float size, u32 color, std::string Text, int maxWidth = 0, int maxHeight = 0, C2D_Font fnt = nullptr);
    void DrawTextLeft(float x, float y, float size, u32 color, std::string Text, int maxWidth = 0, int maxHeight = 0, C2D_Font fnt = nullptr);
	float GetTextWidth(float size, std::string Text, C2D_Font fnt = nullptr);
	void GetTextSize(float size, float *width, float *height, std::string Text, C2D_Font fnt = nullptr);
	float GetTextHeight(float size, std::string Text, C2D_Font fnt = nullptr);
    Result loadFont(C2D_Font &fnt, const char * Path = "");
	Result unloadFont(C2D_Font &fnt);
    bool DrawCircle(float x, float y, float radius, u32 color);
    bool DrawImage(C2D_Image img, float x, float y, float scaleX = 1.0f, float scaleY = 1.0f);
    

    class SpriteSheetAnimation : public RenderD7::Sprite
    {
        public:
        SpriteSheetAnimation();
        ~SpriteSheetAnimation();
        void Setup(RenderD7::Sheet *sheet, size_t imagecount, size_t startimage, float frame_begin, float frame_finish);
        void Play(float timespeed);
        private:
        size_t images;
        size_t imgs = 0;
        float D_totaltime;
        RenderD7::Sheet *sheet;
        float time;
    };
    struct TObject
    {
        int x; //Position X
        int y; //Position Y
        int w; //Button Width
        int h; //Button Height
        std::string text = ""; //Text
        float correctx = 0; //Correct X Position
        float correcty = 0; //Correct Y Position
        float txtsize = 0.7f;  //Set Text Size
    };

    struct TLBtn
    {
        int x; //Position X
        int y; //Position Y
        int w; //Button Width
        int h; //Button Height
    };

    struct ScrollList1 
    {
        std::string Text = "";
    };

    struct ScrollList2 
    {
        float x;
        float y;
        float w;
        float h;
        std::string Text = "";
    };
    /*enum ListType
    {
        ONE,
        TWO
    };*/
    void DrawList1(RenderD7::ScrollList1 &l, float txtsize, C3D_RenderTarget *t);
    void DrawTObjects(std::vector<RenderD7::TObject> tobjects, u32 color, u32 txtcolor,  int selection = -1, u32 selbgcolor = RenderD7::Color::Hex("#2D98AF"), u32 selcolor = RenderD7::Color::Hex("#000000"));
    void DrawSTObject(std::vector<RenderD7::TObject> tobject, int tobjectindex, u32 color, u32 txtcolor);
    bool touchTObj(touchPosition touch, RenderD7::TObject button);
    void DrawTLBtns(std::vector<RenderD7::TLBtn> btns, u32 color,  int selection = -1, u32 selbgcolor = RenderD7::Color::Hex("#2D98AF"), u32 selcolor = RenderD7::Color::Hex("#000000"));
    struct DirContent
    {
        std::string name;
        std::string path;
        bool isDir;
    };
    struct rgba
    {
        int r, g, b, a;
    };
    class Console
    {
         public:
           Console(int x, int y, int w, int h, int a = 255);
           Console(int x, int y, int w, int h, rgba col);
           Console(int x, int y, int w, int h, std::string name, rgba col = {255, 255, 255, 255};, rgba barcol = {0, 0, 0, 255};, rgba outline = {222, 222, 222, 255};);
           ~Console();
         private:
           int x, y, w, h, a;
           rgba color = {255, 255, 255, 255};
           rgba outline = {222, 222, 222, 255};
           rgba barcolor = {0, 0, 0, 255};
    }!

    bool NameIsEndingWith(const std::string &name, const std::vector<std::string> &extensions);
    void GetDirContentsExt(std::vector<RenderD7::DirContent> &dircontent, const std::vector<std::string> &extensions);
    void GetDirContents(std::vector<RenderD7::DirContent> &dircontent);
} /// RenderD7
