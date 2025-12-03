#include <thread>
#include <chrono>
#include <random>
#include <print>
#include <vec3.hpp>
#include "./engine.hpp"

const int TPS = 24;
const float DESIRED_DT = 1.0f / TPS;
std::chrono::duration<float> DESIRED_DT_CHRONO{DESIRED_DT};
std::chrono::milliseconds DESIRED_DT_CHRONO_MS = std::chrono::duration_cast<std::chrono::milliseconds>(DESIRED_DT_CHRONO);
const int N = 10;
// const int NVEC = 5;
const float GFORCE = -9.8f;

const int WALL_HEIGHT = 100;
const int WALL_WIDTH = 50;

void printWall(int width, int height) {
    //std::println("-");
    for (int i = 0; i < width; i++) std::printf("-");
    for (int i = 0; i < height; i++);
}

int main() {

    typedef std::chrono::high_resolution_clock Time;
    typedef std::chrono::milliseconds ms;
    typedef std::chrono::duration<float> fsec;
    typedef std::chrono::seconds sec;

    std::println("\033[2J\033[Hnparticles 0.1.0");
    printWall(WALL_WIDTH, WALL_HEIGHT);

    std::random_device rd; // Obtain a random number from hardware
    std::mt19937 gen(rd()); // Seed the Mersenne Twister engine with a random device
    std::uniform_real_distribution<float> dis(-1.0f, 1.0f); // Define a uniform distribution for floats
    std::this_thread::sleep_for(sec(1));
    std::print("\033[2J\033[H");

    Engine::Point p[N];
    for (int i = 0; i < N; i++) {
        p[i] = Engine::Point(50.0f, 28.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, GFORCE, 1.0f, 1.0f);
    }
    auto prevfinish = Time::now();

    long long frames = 0;
    // sim loop
    while (true) {
        // current time, chrono duration
        auto curriter = Time::now();
        // difference as duration<float>
        fsec deltat = curriter - prevfinish;

        // cast the difference to chronoms
        ms dt = std::chrono::duration_cast<ms>(deltat);
        int fps = 0;
        if (dt.count() > 0) {
            fps = (int) (1000.0f / dt.count());
        }
        std::print("\033[2J\033[H");
        std::println("{}\tFrame: {}\n{}FPS\n{} particles\n", dt, frames, fps, N);
        printWall(WALL_WIDTH, WALL_HEIGHT);
        for (int i = 0; i < N; i++) {
            float fx = dis(gen);
            float fy = dis(gen);
            float fz = dis(gen);
            p[i].doTick(deltat.count(), nvec3::Vec3(fx, fy, fz));
        }
	    frames++;
        auto work_done = Time::now();
        ms work_dt = std::chrono::duration_cast<ms>(work_done - curriter);
        ms tts = DESIRED_DT_CHRONO_MS - work_dt;

        prevfinish = curriter;
        if (tts.count() > 0) {
            std::this_thread::sleep_for(tts);
        }
    }
}
