#include "simulation.hpp"
#include <glm/gtx/quaternion.hpp>

State compute_derivatives(const State &state, const Constants &constants, const ExternalForces &forces) {
    State derivatives;

    // Линейная скорость: v = p / m
    glm::dvec3 velocity = state.momentum / constants.mass;
    derivatives.position = velocity;

    // Вычисление текущего тензора инерции I(t)
    glm::dmat3 rotation = glm::toMat3(state.quaternion);
    glm::dmat3 inertia_tensor_t = rotation * constants.inertia_tensor * glm::transpose(rotation);

    // Угловая скорость: w = I(t)^-1 * L
    glm::dvec3 angular_velocity = glm::inverse(inertia_tensor_t) * state.angular_momentum;

    // Сила Архимеда в зависимости от погруженной части куба
    double offset = 4.0; 
    double submerged_depth = std::max(0.0, -state.position.y + constants.cube_size / 2.0 - offset);
    double submerged_volume = constants.cube_size * constants.cube_size * std::min(submerged_depth, constants.cube_size);
    glm::dvec3 buoyancy_force = glm::dvec3(0.0, forces.rho * 9.81 * submerged_volume, 0.0);

    buoyancy_force.y = std::max(buoyancy_force.y, 0.0);

    // Общая сила (m * g + Архимед + сопротивление)
    glm::dvec3 total_force = constants.mass * forces.gravity + buoyancy_force + forces.drag;
    derivatives.momentum = total_force;

    // Центр масс вытесненного объема жидкости
    glm::dvec3 buoyancy_center = glm::dvec3(0.0, -submerged_depth / 2.0, 0.0);

    // Момент силы Архимеда
    glm::dvec3 torque_buoyancy = glm::cross(buoyancy_center, buoyancy_force);

    // Момент силы сопротивления (если сила приложена в центре масс, момент равен нулю)
    glm::dvec3 torque_drag = glm::dvec3(0.0);

    // Суммарный момент сил
    glm::dvec3 total_torque = torque_buoyancy + torque_drag;

    // Уравнение движения кватерниона: dq/dt = 0.5 * q * omega
    glm::dquat omega_quat(0.0, angular_velocity.x, angular_velocity.y, angular_velocity.z);
    derivatives.quaternion = 0.5 * state.quaternion * omega_quat;

    // Производная углового момента dL/dt = τ
    derivatives.angular_momentum = total_torque;

    return derivatives;
}


void runge_kutta_4(State &state, const Constants &constants, const ExternalForces &forces, double dt) {
    State k1 = compute_derivatives(state, constants, forces);
    State k2 = compute_derivatives(state + k1 * (0.5 * dt), constants, forces);
    State k3 = compute_derivatives(state + k2 * (0.5 * dt), constants, forces);
    State k4 = compute_derivatives(state + k3 * dt, constants, forces);

    state = state + (k1 + k2 * 2.0 + k3 * 2.0 + k4) * (dt / 6.0);

    // Нормализация кватерниона
    state.quaternion = glm::normalize(state.quaternion);
}


void print_energy(const State &state, const Constants &constants) {
    double kinetic_energy = glm::dot(state.momentum, state.momentum) / (2.0 * constants.mass);
    double potential_energy = constants.mass * 9.81 * state.position.y;
    std::cout << "Total Energy: " << (kinetic_energy + potential_energy) << std::endl;
}
