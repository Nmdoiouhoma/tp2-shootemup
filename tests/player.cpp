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

TEST_CASE("Le vaisseau avance selon sa vitesse et le temps écoulé") {
    shootemup::Player player{800.0F, 600.0F};
    const float departX{player.getX()};
    player.update(1.0F, 0.0F, 0.1F);
    REQUIRE_THAT(player.getX(), Catch::Matchers::WithinAbs(departX + 30.0F, 0.001F));
}

TEST_CASE("Le vaisseau ne sort pas par le haut") {
    shootemup::Player player{100.0F, 100.0F};
    player.update(0.0F, -1.0F, 10.0F);
    REQUIRE(player.getY() == 0.0F);
}
