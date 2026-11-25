export module player;

import std;

export namespace shootemup {

    struct Vector2 {
        float x{};
        float y{};
    };

    class Player {
    public:
        Player(float screenWidth, float screenHeight) : screenWidth_{screenWidth}, screenHeight_{screenHeight} {
            position_.x = (screenWidth_ - width_) /2;
            position_.y = screenHeight_ - height_ - bottomMargin_;
        }

        void move(float dx, float dy) {
            position_.x +=  dx ;
            position_.y += dy;
            position_.x = std::clamp(position_.x, 0.0F, screenWidth_ - width_);
            position_.y = std::clamp(position_.y, 0.0F, screenHeight_ - height_);
        }

        float getX() const {
            return position_.x;
        }
       float getY() const {
            return position_.y;
        }

        float getWidth() const {
            return width_;
        }
        float getHeight() const {
            return height_;
        }

        void update(float directionX, float directionY, float deltaSeconds) {
            const float dx{speed_ * directionX * deltaSeconds};
            const float dy{speed_ * directionY * deltaSeconds};
            move(dx, dy);
        }

    private:
        Vector2 position_{};
        float width_{50.0F};
        float height_{50.0F};
        float speed_{300.0F};
        static constexpr float bottomMargin_{20.0F};

        float screenWidth_{};
        float screenHeight_{};
    };


}
