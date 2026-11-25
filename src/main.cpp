#include <SDL3/SDL.h>
import std;
import window;
import sdl;

int main() {
    std::println("Shoot'em up");

    try {
        const shootemup::SdlContext sdlContext{};
        const window::Window window {"Shoot'em up",800, 600 };

        bool isRunning {true};
        while (isRunning) {
            SDL_Event event{};
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_EVENT_QUIT) {
                    isRunning = false;
                }
            }
            SDL_Delay(16);
        }
    }catch (const std::exception &e) {
        std::println("Exception: {}", e.what());
        return 1;
    }
    return 0;
}

