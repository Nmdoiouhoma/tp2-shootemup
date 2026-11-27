export module enemy;
import vector2;
import rectangle;

export namespace shootemup {
    class Enemy {
        public:
        explicit Enemy(Vector2 position) : position_{position} {
        }

        void update(float deltaSeconds) {
            position_.y +=  speed_ * deltaSeconds;
        }

        bool isOffScreen(float screenHeight) const {
            return position_.y > screenHeight;
        }

        float getHeight() const {
            return height_;
        }

        float getWidth() const {
            return width_;
        }
        float getX() const {
            return position_.x;
        }
        float getY() const {
            return position_.y;
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
        float height_{40.0F};
        float width_{40.0F};
        static constexpr float speed_{150.0F};
        bool destroyed_{false};
    };
}
