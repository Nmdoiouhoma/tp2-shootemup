module;
#include <SDL3/SDL.h>

export module window;
import std;
import rectangle;

export namespace window {
    class Window {

    public:
        Window(std::string_view title, int width, int height)
            : window_{SDL_CreateWindow(std::string{title}.c_str(), width, height, SDL_WINDOW_FULLSCREEN), &SDL_DestroyWindow},
              renderer_{SDL_CreateRenderer(window_.get(), nullptr), &SDL_DestroyRenderer} {
            if (!window_) {
                throw std::runtime_error{SDL_GetError()};
            }
            if (!renderer_) {
                throw std::runtime_error{SDL_GetError()};
            }

            SDL_SetRenderLogicalPresentation(renderer_.get(), width, height, SDL_LOGICAL_PRESENTATION_LETTERBOX);
        }

        void clear() {
            SDL_SetRenderDrawColor(renderer_.get(), 0, 0, 0, 255);
            SDL_RenderClear(renderer_.get());
        }

        void drawRectangle(shootemup::Rectangle rectangle) {
            SDL_SetRenderDrawColor(renderer_.get(), 255, 255, 255, 255);
            const SDL_FRect sdlRectangle{rectangle.x, rectangle.y, rectangle.width, rectangle.height};
            SDL_RenderFillRect(renderer_.get(), &sdlRectangle);
        }

        void drawText(std::string_view text, float x, float y, float scale) {
            SDL_SetRenderScale(renderer_.get(), scale, scale);
            SDL_SetRenderDrawColor(renderer_.get(), 255, 255, 255, 255);
            SDL_RenderDebugText(renderer_.get(), x / scale, y / scale, std::string{text}.c_str());
            SDL_SetRenderScale(renderer_.get(), 1.0F, 1.0F);
        }

        void present() {
            SDL_RenderPresent(renderer_.get());
        }

        float textWidth(std::string_view text, float scale) {
            return SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE  * scale * static_cast<float> (text.size());
        }

    private:
        std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window_;
        std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer_;

    };
}
