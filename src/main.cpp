#include <print>
#include <vec3.hpp>
#include <thread>
#include <chrono>
#include "./engine.hpp"

const int TPS = 60;
const float DESIRED_DT = 1.0f / TPS;
std::chrono::duration<float> DESIRED_DT_CHRONO{DESIRED_DT};
std::chrono::milliseconds DESIRED_DT_CHRONO_MS = std::chrono::duration_cast<std::chrono::milliseconds>(DESIRED_DT_CHRONO);
const int N = 99999;
const int NVEC = 5;
const int WALL_HEIGHT = 100;
const int WALL_WIDTH = 50;
const float GFORCE = -9.8f;



int main() {
    typedef std::chrono::high_resolution_clock Time;
    typedef std::chrono::milliseconds ms;
    typedef std::chrono::duration<float> fsec;
    typedef std::chrono::seconds sec;
    std::println("\033[2J\033[Hnparticles 0.1.0");
    std::this_thread::sleep_for(sec(1));
    std::print("\033[2J\033[H");

    Engine::Point p[N];
    for (int i = 0; i < N; i++) {
        p[i] = Engine::Point(50.0f, 28.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, GFORCE, 1.0f);
    }
    auto prevfinish = Time::now();

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
        std::println("\033[2J\033[H {}\n{} FPS\n{} particles\n", dt, fps, N);
        for (int i = 0; i < N; i++) {
            p[i].doTick(deltat.count(), nvec3::Vec3(1.0f, 0.0f, 0.0f));
        }
        for (int i = 0; i < NVEC; i++) std::println("Particle {} : {}", i, p[i].pos);

        auto work_done = Time::now();
        ms work_dt = std::chrono::duration_cast<ms>(work_done - curriter);
        ms tts = DESIRED_DT_CHRONO_MS - work_dt;

        prevfinish = curriter;
        if (tts.count() > 0) {
            std::this_thread::sleep_for(tts);
        }
    }
}
