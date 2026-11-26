import std;
import application;

int main() {
    std::println("Shoot'em up");

    try {
        shootemup::Application application{};
        application.run();
    } catch (const std::exception& e) {
        std::println("Exception: {}", e.what());
        return 1;
    }
    return 0;
}
