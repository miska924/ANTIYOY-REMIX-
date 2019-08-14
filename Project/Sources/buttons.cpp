#include <bits/stdc++.h>
#include <GL/glut.h>
#include "buttons.h"
#include "globals.h"

using namespace std;

void drawButton(int num) {
    double p = SZ / 20;
    double k = p;
    if (button() != num) {
        k = p - SZ * BORDER;
    }
    int c = buttons[num].color;
    if (num == 9) {
        c = WHO % PLAYERS + 1;
    }
    if (c == VOID) {
        c = EMPTY;
    }
    if (c != VOID) {
        glColor4f(CL[c][0], CL[c][1], CL[c][2], 1.0);
        double x = p * (num * 2 + 1);
        double y = p;
        glBegin(GL_POLYGON); {
            glVertex3f(x - k, y - k, 0.1);
            glVertex3f(x - k, y + k, 0.1);
            glVertex3f(x + k, y + k, 0.1);
            glVertex3f(x + k, y - k, 0.1);
        } glEnd();
    }
} 

void drawButtons() {
    for (int i = 0; i < 10; ++i) {
        drawButton(i);
    }
}