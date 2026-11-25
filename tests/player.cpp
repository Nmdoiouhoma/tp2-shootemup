#include <catch2/catch_all.hpp>
import std;
import player;

TEST_CASE("Le vaisseau démarre centré en bas de l'écran") {
    const shootemup::Player player{100.0F, 100.0F};
    CHECK(player.getX() == 25.0F);
    CHECK(player.getY() == 30.0F);
}

TEST_CASE("Le vaisseau ne sort pas par la gauche") {
    shootemup::Player player{100.0F, 100.0F};
    player.move(-1000.0F, 0.0F);
    REQUIRE(player.getX() == 0.0F);
}

TEST_CASE("Le vaisseau ne sort pas par la droite") {
    shootemup::Player player{100.0F, 100.0F};
    player.move(1000.0F, 0.0F);
    REQUIRE(player.getX() == 50.0F);
}
