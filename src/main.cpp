#include <print>
#include <vec3.hpp>
#include <thread>
#include <chrono>

int TPS = 60;

int main() {
    std::print("\033[2J\033[H");
    std::println("nparticles 0.1.0");
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::print("\033[2J\033[H");
    std::this_thread::sleep_for(std::chrono::seconds(2));   
}