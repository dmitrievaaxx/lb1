#ifndef STATE_HPP
#define STATE_HPP

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

struct State {
    glm::dvec3 position; // координаты центра масс тела в трехмерном пространстве
    glm::dvec3 momentum; // импульс (p = m * v)
    glm::dquat quaternion; // кватернион
    glm::dvec3 angular_momentum; // угловой момент тела (L = I * w, где I - тензор энерции, w - угловая скорость)

    State operator*(double scalar) const;
    State operator+(const State& other) const;
};

struct Constants {
    double mass;
    glm::dmat3 inertia_tensor;
};

struct ExternalForces {
    glm::dvec3 gravity;
    glm::dvec3 buoyancy; // сила Архимеда
    glm::dvec3 drag; // сила сопротивления среды
};

#endif