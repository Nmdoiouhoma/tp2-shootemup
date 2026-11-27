export module collision;
import std;
import player;
import projectile;
import enemy;
import rectangle;

export namespace shootemup {


    bool intersects(Rectangle  first, Rectangle  second) {

        //cas 1
        if (first.x + first.width <= second.x) {
            return false;
        }

        // caas 2
        if (first.x >= second.x + second.width) {
            return false;
        }

        //cas 3
        if (first.y + first.height <= second.y) {
            return false;
        }

        // cas 4
        if (first.y >= second.y + second.height) {
            return false;
        }
        return true;
    }


    class CollisionManager {
    public:
        void handleProjectilesHitEnemies(std::vector<Projectile>& projectiles, std::vector<Enemy>& enemies) {
            for (auto& projectile : projectiles) {

                for (auto& enemy : enemies) {
                    if (intersects(projectile.getBounds(), enemy.getBounds())) {
                        projectile.destroy();
                        enemy.destroy();
                    }
                }
            }
        }

        bool isPlayerHit(const Player& player, const std::vector<Enemy>& enemies) const {
            for (const auto& enemy : enemies) {
                if (intersects(player.getBounds(), enemy.getBounds())) {
                    return true;
                }
            }
            return false;
        }
    };
}




