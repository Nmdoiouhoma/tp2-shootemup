module;
#include <SDL3/SDL.h>
export module application;
import std;
import sdl;
import player;
import projectile;
import window;

export namespace shootemup {
    class Application {
        public:
        Application()
            : window_{"Shoot'em up", screenWidth_, screenHeight_},
              player_{screenWidth_, screenHeight_} {}

        void run() {
            while (isRunning_) {
                const auto currentTime{std::chrono::steady_clock::now()};
                const std::chrono::duration<float> elapsed{currentTime - previousTime_};
                previousTime_ = currentTime;

                handleEvents();
                update(elapsed.count());
                render();
                SDL_Delay(16);
            }
        }

        private:
        void handleEvents() {
            SDL_Event event{};
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_EVENT_QUIT) {
                    isRunning_ = false;
                }
                if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE) {
                    isRunning_ = false;
                }
                if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_SPACE) {
                    const float projectileX{player_.getX() + player_.getWidth() / 2.0F - 2.5F};
                    const float projectileY{player_.getY()};
                    const Vector2 startPosition{projectileX, projectileY};
                    projectiles_.push_back(Projectile{startPosition});
                }
            }
        }

        void update(float deltaSeconds) {
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
            player_.update(directionX, directionY, deltaSeconds);

            for (auto& projectile : projectiles_) {
                projectile.update(deltaSeconds);
            }
            std::erase_if(projectiles_, [](const Projectile& projectile) {
                return projectile.isOffScreen();
            });
        }

        void render() {
            window_.clear();
            window_.drawRectangle(player_.getX(), player_.getY(), player_.getWidth(), player_.getHeight());
            for (const auto& projectile : projectiles_) {
                window_.drawRectangle(projectile.getX(), projectile.getY(), projectile.getWidth(), projectile.getHeight());
            }
            window_.present();
        }

        static constexpr int screenWidth_{800};
        static constexpr int screenHeight_{600};

        SdlContext sdlContext_;
        window::Window window_;
        Player player_;
        std::vector<Projectile> projectiles_{};
        bool isRunning_{true};
        std::chrono::steady_clock::time_point previousTime_{std::chrono::steady_clock::now()};
    };
}
