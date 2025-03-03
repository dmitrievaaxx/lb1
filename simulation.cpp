#include "simulation.hpp"
#include <glm/gtx/quaternion.hpp>


State compute_derivatives(const State &state, const Constants &constants, const ExternalForces &forces) {
    State derivatives;

    // Линейная скорость тела v = p / m
    glm::dvec3 velocity = state.momentum / constants.mass;
    derivatives.position = velocity; // Скорость - производная координаты по времени

    // Угловая скорость тела w = I^-1 * L
    glm::dvec3 angular_velocity = glm::inverse(constants.inertia_tensor) * state.angular_momentum;

    // Общая сила, действующая на тело (гравитация, сила Архимеда и сопротивление)
    glm::dvec3 total_force = forces.gravity + forces.buoyancy + forces.drag;
    derivatives.momentum = total_force; // Сила - производная импульса по времени

    // Уравнение движения кватерниона: dq/dt = (1/2) * q * ω
    // q — текущая ориентация тела (кватернион),
    // ω — угловая скорость, представленная как чисто векторный кватернион (0, wx, wy, wz).
    glm::dquat omega_quat(0.0, angular_velocity.x, angular_velocity.y, angular_velocity.z);
    derivatives.quaternion = 0.5 * state.quaternion * omega_quat;

    // Угловой момент остается неизменным, так как в данной модели отсутствует внешний момент силы
    derivatives.angular_momentum = glm::dvec3(0.0);

    return derivatives;
}


void runge_kutta_4(State &state, const Constants &constants, const ExternalForces &forces, double dt) {
    // Численное интегрирование уравнений движения методом Рунге-Кутты 4-го порядка
    State k1 = compute_derivatives(state, constants, forces);
    State k2 = compute_derivatives(state + k1 * (0.5 * dt), constants, forces);
    State k3 = compute_derivatives(state + k2 * (0.5 * dt), constants, forces);
    State k4 = compute_derivatives(state + k3 * dt, constants, forces);

    // Обновляем состояние тела
    state = state + (k1 + k2 * 2.0 + k3 * 2.0 + k4) * (dt / 6.0);

    // Нормализуем кватернион
    state.quaternion = glm::normalize(state.quaternion);
}
