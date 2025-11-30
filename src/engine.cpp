#include "engine.hpp"

void Engine::Point::doTick(float deltat, nvec3::Vec3 force) {
    this->accel = (force / this->mass) + this->gravity;
    this->pos += (this->vel * deltat) + (0.5f * this->accel * deltat * deltat);
    this->vel += (this->accel * deltat);
}