module;
#include <SDL3/SDL.h>
export module application;
import std;
import sdl;
import player;
import projectile;
import window;
import vector2;
import enemy;
import collision;

export namespace shootemup {


    enum class GameState {
        Playing,
        GameOver,
    };

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

                if (gameState_ == GameState::Playing) {
                    update(elapsed.count());
                }
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
                if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_SPACE && gameState_ == GameState::Playing) {
                    const float projectileX{player_.getX() + player_.getWidth() / 2.0F - 2.5F};
                    const float projectileY{player_.getY()};
                    const Vector2 startPosition{projectileX, projectileY};
                    projectiles_.push_back(Projectile{startPosition});
                }
                if (gameState_ == GameState::GameOver && event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_RETURN) {
                    restart();
                }
            }
        }

        void update(float deltaSeconds) {
            updatePlayer(deltaSeconds);
            updateObjects(deltaSeconds);
            handleCollisions();
            handleEnemiesPassed();
            if (lives_ <= 0) {
                gameState_ = GameState::GameOver;
            }
            removeDeadObjects();
            spawnEnemies(deltaSeconds);
        }

        void restart() {
            score_ = 0;
            lives_ = startingLives_;
            gameState_ = GameState::Playing;
            player_ = Player{screenWidth_, screenHeight_};
            projectiles_.clear();
            enemies_.clear();
            spawnTimer_ = 0.0F;

        }
        void updatePlayer(float deltaSeconds) {
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
        }

        void updateObjects(float deltaSeconds) {
            for (auto& projectile : projectiles_) {
                projectile.update(deltaSeconds);
            }
            for (auto& enemy : enemies_) {
                enemy.update(deltaSeconds);
            }
        }

        void handleCollisions() {
            const int countDestroyedEnemies = collisionManager_.handleProjectilesHitEnemies(projectiles_, enemies_);
            score_ += countDestroyedEnemies * pointsPerEnemy_;
            if (collisionManager_.isPlayerHit(player_, enemies_)) {
                lives_--;
            }
        }

        void removeDeadObjects() {
            std::erase_if(projectiles_, [](const Projectile& projectile) {
                return projectile.isOffScreen() || projectile.isDestroyed();
            });
            std::erase_if(enemies_, [](const Enemy& enemy) {
                return enemy.isOffScreen(screenHeight_) || enemy.isDestroyed();
            });
        }

        void spawnEnemies(float deltaSeconds) {
            spawnTimer_ += deltaSeconds;
            if (spawnTimer_ > currentSpawnInterval_) {
                const Vector2 startPosition{spawnX_(randomEngine_), -40.0F};
                enemies_.push_back(Enemy{startPosition});
                spawnTimer_ = 0.0F;
                currentSpawnInterval_ -= spawnIntervalDecrease_;
                currentSpawnInterval_ = std::max(currentSpawnInterval_, minimumSpawnInterval_);
            }
        }

        void handleEnemiesPassed() {
            for (const auto& enemy : enemies_){
                if (enemy.isOffScreen(screenHeight_)) {
                    lives_--;
                }
            }
        }

        void render() {
            window_.clear();
            window_.drawRectangle(player_.getBounds());
            for (const auto& projectile : projectiles_) {
                window_.drawRectangle(projectile.getBounds());
            }
            for (const auto& enemy : enemies_)  {
                window_.drawRectangle(enemy.getBounds());
            }
            if (gameState_ == GameState::GameOver) {
                const float titleX{(screenWidth_ - window_.textWidth("GAME OVER", 4.0F)) / 2};
                window_.drawText("GAME OVER", titleX, 280.0F, 4.0F);
                const std::string scoreText{std::format("Score : {}", score_)};
                const float scoreX{(screenWidth_ - window_.textWidth(scoreText, 2.0F)) / 2};
                window_.drawText(scoreText, scoreX, 330.0F, 2.0F);
            }
            window_.present();
        }

        static constexpr int screenWidth_{800};
        static constexpr int screenHeight_{600};
        static constexpr float minimumSpawnInterval_{0.3F};
        static constexpr float spawnIntervalDecrease_{0.02F};
        float currentSpawnInterval_{spawnInterval_};

        std::mt19937 randomEngine_{std::random_device{}()};
        std::uniform_real_distribution<float> spawnX_{0.0F, (static_cast<float> (screenWidth_ - 40.0F))};

        static constexpr float  spawnInterval_{1.0F};
        static constexpr int pointsPerEnemy_{10};
        static constexpr int startingLives_{3};

        SdlContext sdlContext_;
        window::Window window_;
        Player player_;
        std::vector<Projectile> projectiles_{};
        std::vector<Enemy> enemies_;
        float spawnTimer_{0.0F};
        bool isRunning_{true};
        std::chrono::steady_clock::time_point previousTime_{std::chrono::steady_clock::now()};
        CollisionManager collisionManager_{};
        int lives_{startingLives_};
        int score_{0};
       GameState gameState_ {GameState::Playing};
    };
}
