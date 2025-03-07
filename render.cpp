#include "render.hpp"
#include "simulation.hpp"
#include <glm/gtc/matrix_transform.hpp>

extern State state;
extern Constants constants;
extern ExternalForces forces;
extern double simulation_time; // Текущее время в симуляции
extern double dt; // Шаг интегрирования

void initOpenGL() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    
}

void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(0.0, 5.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glPushMatrix();
    glTranslatef(state.position.x, state.position.y, state.position.z);

    state.quaternion = glm::normalize(state.quaternion);

    glm::dquat q = state.quaternion;
    float angle = glm::degrees(glm::angle(q));
    glm::dvec3 axis = glm::axis(q);
    glRotatef(angle, axis.x, axis.y, axis.z);
    glutWireCube(1.0);
    glPopMatrix();

    glutSwapBuffers();
}

void update(int value) {
    runge_kutta_4(state, constants, forces, dt);
    simulation_time += dt;

    print_energy(state, constants);
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
}
