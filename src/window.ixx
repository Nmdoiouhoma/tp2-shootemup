module;
#include <SDL3/SDL.h>

export module window;

import std;

export namespace window {


    class Window {
    public:
        Window(std::string_view title, int width, int height)
            : window_{SDL_CreateWindow(std::string{title}.c_str(), width, height, 0), &SDL_DestroyWindow} {
            if (!window_) {
                throw std::runtime_error{SDL_GetError()};
            }
        }

    private:
        std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window_;

    };

    class Application {

    };

}