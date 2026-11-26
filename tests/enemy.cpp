#include <catch2/catch_all.hpp>
import std;
import vector2;
import enemy;

TEST_CASE("L'ennemi descend selon sa vitesse et le temps écoulé") {
    shootemup::Enemy enemy{shootemup::Vector2{100.0F, 300.0F}};
    const float departY{enemy.getY()};
    enemy.update(0.1F);
    REQUIRE_THAT(enemy.getY(), Catch::Matchers::WithinAbs(departY + 15.0F, 0.001F));
}

TEST_CASE("L'ennemi sort par le bas de l'écran") {
    shootemup::Enemy enemy{shootemup::Vector2{100.0F, 300.0F}};
    REQUIRE_FALSE(enemy.isOffScreen(600.0F));
    enemy.update(3.0F);
    REQUIRE(enemy.isOffScreen(600.0F));
}
