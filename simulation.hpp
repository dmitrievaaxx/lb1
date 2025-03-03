#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "state.hpp"

State compute_derivatives(const State& state, const Constants& constants, const ExternalForces& forces);

void runge_kutta_4(State& state, const Constants& constants, const ExternalForces& forces, double dt);

#endif
