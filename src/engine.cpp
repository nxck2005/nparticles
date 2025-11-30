#include "engine.hpp"

void Engine::Point::doTick(float deltat, nvec3::Vec3 force) {
    this->accel = (force) / this->mass;
    this->vel += (this->accel * deltat);
    this->pos = (this->vel * deltat) + (0.5 * this->accel * deltat * deltat);
}