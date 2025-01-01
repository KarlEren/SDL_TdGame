#pragma once
#include "manager.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>


class GameManager:public Manager<GameManager>
{
    friend class Manager<GameManager>;//使父类GameManager可以访问子类构造函数
    
public:
     int run(int argc,char**argv)//主循环函数
     {
         Uint64 last_counter=SDL_GetPerformanceCounter();
         const Uint64 counter_freq=SDL_GetPerformanceFrequency();
         
         while (!is_quit)
         {
             while (SDL_PollEvent(&event))on_input();
             Uint64 curr_counter=SDL_GetPerformanceCounter();
             double delta=static_cast<double>(curr_counter-last_counter/counter_freq);
             last_counter=curr_counter;
             if (delta*1000<1000.0/60)SDL_Delay(static_cast<Uint32>(1000.0/60-delta*1000));
             on_update(delta);
             SDL_SetRenderDrawColor(renderer,0,0,0,255);
             SDL_RenderClear(renderer);
             on_render();
             SDL_RenderPresent(renderer);
         }
         return 0;
     }
    
protected:
    GameManager()
    {
        init_assert(!SDL_Init(SDL_INIT_EVERYTHING),u8"SDL2 Init failed");
        init_assert(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG),u8"SDL_Image Init failed");
        init_assert(Mix_Init(MIX_INIT_MP3),u8"SDL_Music init failed");
        init_assert(!TTF_Init(),u8"TTF Init failed");
        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
        SDL_SetHint(SDL_HINT_IME_SHOW_UI,"1");//向SDL提供建议，使得用户在输入中文时可以显示中文输入法
        window=SDL_CreateWindow(u8"Village Defense",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1280,720,SDL_WINDOW_SHOWN);//创建游戏窗口
        init_assert(window,u8"Window Creation Error");
        renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);//创建渲染器启用硬件加速和垂直同步.-1是驱动索引,把渲染目标改为纹理
        init_assert(renderer,u8"Renderer Creation Error");
        
    }

    ~GameManager()
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        Mix_Quit();
        IMG_Quit();
        SDL_Quit();
    }
    
private:
    
    SDL_Event event;
    bool is_quit=false;
    SDL_Window* window=nullptr;
    SDL_Renderer* renderer=nullptr;

     void init_assert(bool flag,const char*err_msg)//检查SDL各模块是否初始化成功的断言函数
     {
         if (flag)return;
         SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,u8"Game Start Failed",err_msg,window);//弹出消息窗口
         exit(-1);
     }

    void on_input(){}
    void on_update(double delta){}
    void on_render(){}
    
};
