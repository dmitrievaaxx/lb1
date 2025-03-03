#include "state.hpp"

State State::operator*(double scalar) const {
    State result;
    result.position = this->position * scalar;
    result.momentum = this->momentum * scalar;
    result.quaternion = this->quaternion * scalar;
    result.angular_momentum = this->angular_momentum * scalar;
    return result;
}

State State::operator+(const State& other) const {
    State result;
    result.position = this->position + other.position;
    result.momentum = this->momentum + other.momentum;
    result.quaternion = this->quaternion + other.quaternion;
    result.angular_momentum = this->angular_momentum + other.angular_momentum;
    return result;
}