#include <bits/stdc++.h>
#include <GL/glut.h>
#include "globals.h"

using namespace std;

void drawInfo() {
    glColor4f(CL[WHO][0], CL[WHO][1], CL[WHO][2], 1);
    glBegin(GL_POLYGON); {
        glVertex2f(1, -1);
        glVertex2f(1, 21);
        glVertex2f(-1, 21);
        glVertex2f(-1, -1);
    } glEnd();
    glBegin(GL_POLYGON); {
        glVertex2f(-1, 1);
        glVertex2f(21, 1);
        glVertex2f(21, -1);
        glVertex2f(-1, -1);
    } glEnd();
    glBegin(GL_POLYGON); {
        glVertex2f(19, -1);
        glVertex2f(19, 21);
        glVertex2f(21, 21);
        glVertex2f(21, -1);
    } glEnd();
    glBegin(GL_POLYGON); {
        glVertex2f(-1, 19);
        glVertex2f(21, 19);
        glVertex2f(21, 21);
        glVertex2f(-1, 21);
    } glEnd();
}