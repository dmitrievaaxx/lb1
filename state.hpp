#ifndef STATE_HPP
#define STATE_HPP

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

struct State {
    glm::dvec3 position; // Координаты центра масс тела в трехмерном пространстве
    glm::dvec3 momentum; // Импульс (p = m * v)
    glm::dquat quaternion; // Кватернион
    glm::dvec3 angular_momentum; // Угловой момент тела (L = I * w, где I - тензор энерции, w - угловая скорость)

    State operator*(double scalar) const;
    State operator+(const State& other) const;
};

struct Constants {
    double mass;
    glm::dmat3 inertia_tensor;
    double cube_size;
};

struct ExternalForces {
    glm::dvec3 gravity;
    glm::dvec3 buoyancy; // Сила Архимеда
    glm::dvec3 drag; // Сила сопротивления среды
    double rho; // Плотность жидкости для вычисления силы Архимеда
};

#endif
