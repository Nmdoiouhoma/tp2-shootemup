export module projectile;
import std;
import vector2;
import rectangle;

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

        Rectangle getBounds() const {
            Rectangle rectangle{position_.x, position_.y, width_, height_};
            return rectangle;
        }

        void destroy() {
            destroyed_ = true;
        }

        bool isDestroyed() const {
            return destroyed_;
        }

        private:

        Vector2 position_{0.0F, 0.0F};
        float height_{15.0F};
        float width_{5.0F};
        static constexpr float speed_{600.0F};
        bool destroyed_{false};

    };
}
