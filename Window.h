#ifndef WINDOW
#define WINDOW

#include <stdio.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <SDL_syswm.h>
#include <SDL.h>

namespace RachitEngine {
    class Window {
    private:
        bgfx::PlatformData pd;
        SDL_Window* window;
        int width, height;

    public:
        Window(const char* title, int width, int height);
        ~Window();
        void Update();
    };
};

#endif