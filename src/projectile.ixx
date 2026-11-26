export module projectile;
import std;
import vector2;


export namespace shootemup {
    class Projectile {
        public:
        explicit Projectile(Vector2 position) : position_{position} {}

        void update(float deltaSeconds) {
            position_.y -=  speed_ * deltaSeconds;
        }

        bool isOffScreen() const {
            return position_.y + height_ < 0.0F;
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

        private:

        Vector2 position_{0.0F, 0.0F};
        float height_{15.0F};
        float width_{5.0F};
        static constexpr float speed_{600.0F};

    };
}
