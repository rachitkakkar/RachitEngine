class Window {
private:
    bool quit;
    SDL_Window* window;

public:
    Window(const char* title, int width, int height);
    ~Window();
};