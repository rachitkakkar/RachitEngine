#include "Window.h"

namespace RachitEngine {
    Window::Window(const char* title, int w, int h) {
        if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
            printf("SDL could not initialize! SDL_Error: %s\n",
                SDL_GetError());
        }

        width = w; height = h;
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
        
        if (window == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }

        SDL_SysWMinfo wmi;
        SDL_VERSION(&wmi.version);
        if (!SDL_GetWindowWMInfo(window, &wmi)) {
            printf("SDL_SysWMinfo could not be retrieved. SDL_Error: %s\n",
                SDL_GetError());
        }
#if BX_PLATFORM_WINDOWS
        pd.nwh = wmi.info.win.window;
#elif BX_PLATFORM_OSX
        pd.nwh = wmi.info.cocoa.window;
#elif BX_PLATFORM_LINUX
        pd.ndt = wmi.info.x11.display;
        pd.nwh = (void*)(uintptr_t)wmi.info.x11.window;
#endif // BX_PLATFORM_WINDOWS ? BX_PLATFORM_OSX ? BX_PLATFORM_LINUX
        bgfx::setPlatformData(pd);
        bgfx::renderFrame();
        bgfx::Init bgfx_init;
        bgfx_init.type = bgfx::RendererType::Count;
        bgfx_init.resolution.width = width;
        bgfx_init.resolution.height = height;
        bgfx_init.resolution.reset = BGFX_RESET_VSYNC;
        bgfx_init.platformData = pd;
        bgfx::init(bgfx_init);
        bgfx::reset(width, height, BGFX_RESET_VSYNC);
#ifdef RACHITENGINE_DEBUG
        bgfx::setDebug(BGFX_DEBUG_TEXT /*| BGFX_DEBUG_STATS*/);
#endif
        bgfx::setViewRect(0, 0, 0, uint16_t(width), uint16_t(height));
    }

    Window::~Window() {
        bgfx::shutdown();
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void Window::Update() {
        bgfx::frame();
    }
};