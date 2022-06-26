#include "Window.h"

Window:Window(const char* title, int width, int height) {
    quit = false;
    bgfx::ProgramHandle program = BGFX_INVALID_HANDLE;
    bgfx::VertexBufferHandle vbh = BGFX_INVALID_HANDLE;
    bgfx::IndexBufferHandle ibh = BGFX_INVALID_HANDLE;

    SDL_Window* window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        printf("Window could not be created. SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
}

Window:~Window() {
    bgfx::destroy(vbh);
    bgfx::destroy(ibh);
    bgfx::destroy(program);
    bgfx::shutdown();

    SDL_DestroyWindow(window);
    SDL_Quit();
}