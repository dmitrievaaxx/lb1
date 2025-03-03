#ifndef RENDER_HPP
#define RENDER_HPP

#include <GL/glut.h>
#include "state.hpp"
#include "simulation.hpp"

void initOpenGL();
void drawScene();
void reshape(int w, int h);
void update(int value);

#endif
