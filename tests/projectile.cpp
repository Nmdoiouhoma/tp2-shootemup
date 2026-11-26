#include <catch2/catch_all.hpp>
import std;
import player;
import projectile;

TEST_CASE("Le tir monte selon sa vitesse et le temps écoulé") {
    shootemup::Projectile projectile{shootemup::Vector2{100.0F, 300.0F}};
    const float departY{projectile.getY()};
    projectile.update(0.1F);
    REQUIRE_THAT(projectile.getY(), Catch::Matchers::WithinAbs(departY - 60.0F, 0.001F));
}

TEST_CASE("Le tir sort par le haut de l'écran") {
    shootemup::Projectile projectile{shootemup::Vector2{100.0F, 300.0F}};
    REQUIRE_FALSE(projectile.isOffScreen());
    projectile.update(1.0F);
    REQUIRE(projectile.isOffScreen());
}
