#include <SDL3/SDL.h>
import std;
import window;
import sdl;

int main() {
    std::println("Shoot'em up");

    try {
        const shootemup::SdlContext sdlContext{};
        const window::Window window {"Shoot'em up",800, 600 };
        SDL_Delay(10000);

    }catch (const std::exception &e) {
        std::println("Exception: {}", e.what());
        return 1;
    }
    return 0;
}

