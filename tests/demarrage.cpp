#include <catch2/catch_all.hpp>
import std;

TEST_CASE("Le projet de tests compile et s'exécute") {
    REQUIRE(std::string_view{"ok"}.size() == 2);
}
