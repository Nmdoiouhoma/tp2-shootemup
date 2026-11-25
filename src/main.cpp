#include <SDL3/SDL.h>
import std;
import window;
import sdl;
import player;

int main() {
    std::println("Shoot'em up");

    try {
        const shootemup::SdlContext sdlContext{};
        constexpr int screenWidth{800};
        constexpr int screenHeight{600};
        window::Window window {"Shoot'em up",screenWidth, screenHeight };
        shootemup::Player player  {screenWidth, screenHeight };

        bool isRunning {true};
        while (isRunning) {
            SDL_Event event{};
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_EVENT_QUIT) {
                    isRunning = false;
                }
            }
            window.clear();
            window.drawRectangle(player.getX(), player.getY(), player.getWidth(), player.getHeight());
            window.present();
            SDL_Delay(16);
        }
    }catch (const std::exception &e) {
        std::println("Exception: {}", e.what());
        return 1;
    }
    return 0;
}

