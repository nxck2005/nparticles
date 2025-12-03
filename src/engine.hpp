#include <vec3.hpp>

namespace Engine {
    class Point {
        public:
            nvec3::Vec3 pos;
            nvec3::Vec3 vel;
            nvec3::Vec3 accel;
            nvec3::Vec3 gravity;
            float mass;
            float radius;

            constexpr Point(float px, float py, float pz, float vx, float vy, float vz,
                float ax, float ay, float az, float g, float m, float rad) :
                pos(px, py, pz), vel(vx, vy, vz),
                accel(ax, ay, az), gravity(0.0f, g, 0.0f), mass(m), radius(rad) {}

            constexpr Point(): pos(0.0f, 0.0f, 0.0f), vel(0.0f, 0.0f, 0.0f),
                accel(0.0f, 0.0f, 0.0f), gravity(0.0f, -9.8f, 0.0f), mass(1.0f), radius(1.0f) {}

            void doTick(float deltat, nvec3::Vec3 force);
    };
}
