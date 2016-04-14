#include "DynamicSimulator.hpp"

namespace uwv_dynamic_model
{
/**********************************************************
 * Dynamic Simulator
 * Defines velocity derivatives for the dynamic simulation
 **********************************************************/
DynamicSimulator::DynamicSimulator( double integration_step):
        RK4Integrator(integration_step) {}

DynamicSimulator::~DynamicSimulator()
{}

PoseVelocityState DynamicSimulator::velocityDeriv(const PoseVelocityState &current_states, const base::Vector6d &control_input)
{
    base::Vector6d velocity;
    velocity.head(3) = current_states.linear_velocity;
    velocity.tail(3) = current_states.angular_velocity;

    // Compute acceleration (velocity derivatives)
    base::Vector6d acceleration = gDynamicModel.calcAcceleration(control_input, velocity, current_states.orientation);

    PoseVelocityState deriv;
    deriv.linear_velocity = acceleration.head<3>();
    deriv.angular_velocity = acceleration.tail<3>();

    gAcceleration.linear_acceleration = acceleration.head<3>();
    gAcceleration.angular_acceleration = acceleration.tail<3>();

    return deriv;
}

PoseVelocityState DynamicSimulator::poseDeriv(const PoseVelocityState &current_states)
{
    PoseVelocityState ret;
    return 0*ret;
}

AccelerationState DynamicSimulator::getAcceleration() const
{
    return gAcceleration;
}

DynamicModel* DynamicSimulator::getDynamicModel()
{
    return &gDynamicModel;
}
};
