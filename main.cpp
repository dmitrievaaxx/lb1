#include "render.hpp"
#include "simulation.hpp"

State state;
Constants constants;
ExternalForces forces;
double simulation_time = 0.0;
double dt = 0.01;

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Physics Simulation with OpenGL");

    // Инициализация состояния тела
    state.position = glm::dvec3(0.0, 0.0, 0.0);
    state.momentum = glm::dvec3(0.0, 0.0, 0.0);
    state.quaternion = glm::dquat(1.0, 0.0, 0.0, 0.0);
    state.angular_momentum = glm::dvec3(0.0, 0.0, 0.0);

    // Инициализация констант тела
    constants.mass = 1.0;
    constants.inertia_tensor = glm::dmat3(1.0);

    // Инициализация внешних сил
    forces.gravity = glm::dvec3(0.0, -9.81, 0.0);
    forces.buoyancy = glm::dvec3(0.0, 9.81, 0.0);
    forces.drag = glm::dvec3(-0.1, 0.0, 0.0);

    initOpenGL();

    glutDisplayFunc(drawScene);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, update, 0);

    glutMainLoop();

    return 0;
}
