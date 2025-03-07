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
    state.position = glm::dvec3(5.0, 3.0, 0.0);
    state.momentum = glm::dvec3(0.0, 0.0, 0.0);
    state.quaternion = glm::dquat(1.0, 0.0, 0.0, 0.0);
    state.angular_momentum = glm::dvec3(0.0, 0.0, 0.0);

    // Инициализация констант тела
    constants.mass = 1.0;
    constants.cube_size = 1.0;
    double I = (1.0 / 6.0) * constants.mass * constants.cube_size * constants.cube_size;
    constants.inertia_tensor = glm::dmat3(
        I, 0.0, 0.0, 
        0.0, I, 0.0, 
        0.0, 0.0, I  
    );

    // Инициализация внешних сил
    forces.gravity = glm::dvec3(0.0, -9.81, 0.0);
    forces.rho = 1000.0;
    forces.drag = glm::dvec3(-0.1, 0.0, 0.0);

    initOpenGL();
    glutDisplayFunc(drawScene);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    return 0;
}
