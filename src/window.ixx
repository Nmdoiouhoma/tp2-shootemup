module;
#include <SDL3/SDL.h>

export module window;
import std;

export namespace window {
    class Window {

    public:
        Window(std::string_view title, int width, int height)
            : window_{SDL_CreateWindow(std::string{title}.c_str(), width, height, 0), &SDL_DestroyWindow},
              renderer_{SDL_CreateRenderer(window_.get(), nullptr), &SDL_DestroyRenderer} {
            if (!window_) {
                throw std::runtime_error{SDL_GetError()};
            }
            if (!renderer_) {
                throw std::runtime_error{SDL_GetError()};
            }
        }

        void clear() {
            SDL_SetRenderDrawColor(renderer_.get(), 0, 0, 0, 255);
            SDL_RenderClear(renderer_.get());
        }

        void drawRectangle(float x, float y, float width, float height) {
            SDL_SetRenderDrawColor(renderer_.get(), 255, 255, 255, 255);
            const SDL_FRect rectangle{x, y, width, height};
            SDL_RenderFillRect(renderer_.get(), &rectangle);
        }

        void present() {
            SDL_RenderPresent(renderer_.get());
        }

    private:
        std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window_;
        std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer_;

    };

    class Application {

    };

}