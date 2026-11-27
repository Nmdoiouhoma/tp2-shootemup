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
        int handleProjectilesHitEnemies(std::vector<Projectile>& projectiles, std::vector<Enemy>& enemies) {
            auto count {0};
            for (auto& projectile : projectiles) {
                for (auto& enemy : enemies) {
                    if (intersects(projectile.getBounds(), enemy.getBounds()) && !enemy.isDestroyed()) {
                        projectile.destroy();
                        enemy.destroy();
                        count++;
                    }
                }
            }
            return count;
        }

        bool isPlayerHit(const Player& player, std::vector<Enemy>& enemies) const {
            for (auto& enemy : enemies) {
                if (intersects(player.getBounds(), enemy.getBounds())) {
                    enemy.destroy();
                    return true;
                }
            }
            return false;
        }
    };
}




