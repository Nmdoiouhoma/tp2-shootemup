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
        auto previousTime{std::chrono::steady_clock::now()};
        while (isRunning) {
            const auto currentTime{std::chrono::steady_clock::now()};
            const std::chrono::duration<float> elapsed{currentTime - previousTime};
            previousTime = currentTime;

            SDL_Event event{};
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_EVENT_QUIT) {
                    isRunning = false;
                }
               if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE) {
                    isRunning = false;
                }
            }

            const bool* keys{SDL_GetKeyboardState(nullptr)};
            float directionX{0.0F};
            float directionY{0.0F};

            if (keys[SDL_SCANCODE_LEFT] == true) {
                directionX -= 1.0F;
            }
            if (keys[SDL_SCANCODE_RIGHT] == true) {
                directionX += 1.0F;
            }

            if (keys[SDL_SCANCODE_UP] == true) {
                directionY -= 1.0F;
            }
            if (keys[SDL_SCANCODE_DOWN] == true) {
                directionY += 1.0F;
            }
            player.update(directionX, directionY, elapsed.count());
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

