#include <bits/stdc++.h>
#include <GL/glut.h>
#include "primitives.h"
#include "globals.h"

using namespace std;

void drawCircle(double x, double y, double r, double color, double z) {
    glColor4f(color, color, color, 1.0);
    glBegin(GL_POLYGON); {
        for (int i = 0; i < 360; i += 20) {
            double a = ang(i);
            glVertex3f(x + r * cos(a), y + r * sin(a), z);
        }
    } glEnd();
}

void drawCircleEmpty(double x, double y, double r, double color, double z) {
    glColor4f(color, color, color, 1.0);
    glBegin(GL_LINES); {
        for (int i = 0; i < 360; i += 20) {
            double a = ang(i);
            double b = ang(i + 20);
            glVertex3f(x + r * cos(a), y + r * sin(a), z);
            glVertex3f(x + r * cos(b), y + r * sin(b), z);
        }
    } glEnd();
}

void drawLine(double x0, double y0, double x1, double y1, double color, double z) {
    glColor4f(color, color, color, 1.0);
    glBegin(GL_LINES); {
        glVertex3f(x0, y0, z);
        glVertex3f(x1, y1, z);
    } glEnd();
}

// void drawSquare(double x, double y, double rib) {
//     glColor4f(1.0, 1.0, 1.0, 1.0);
//     glBegin(GL_POLYGON); {
//         glVertex3f(x - rib / 2, y - rib / 2, 0.1);
//         glVertex3f(x + rib / 2, y - rib / 2, 0.1);
//         glVertex3f(x + rib / 2, y + rib / 2, 0.1);
//         glVertex3f(x - rib / 2, y + rib / 2, 0.1);
//     } glEnd();

//     glColor4f(1.0, 1.0, 1.0, 1.0);
//     glBegin(GL_POLYGON); {
//         glVertex3f(x - rib / 2, y - rib / 2, 0.1);
//         glVertex3f(x + rib / 2, y - rib / 2, 0.1);
//         glVertex3f(x + rib / 2, y + rib / 2, 0.1);
//         glVertex3f(x - rib / 2, y + rib / 2, 0.1);
//     } glEnd();
// }

void drawCrown(double x, double y, double r, double z) {
    glColor4f(1.0, 1.0, 0.0, 1.0);
    glBegin(GL_POLYGON); {
        glVertex3f(x        , y        , z);
        glVertex3f(x - r    , y        , z);
        glVertex3f(x - r    , y + r    , z);
        glVertex3f(x - r / 3, y + r / 3, z);
        glVertex3f(x        , y + r    , z);
        glVertex3f(x + r / 3, y + r / 3, z);
        glVertex3f(x + r    , y + r    , z);
        glVertex3f(x + r    , y        , z);
        glVertex3f(x        , y        , z);
    } glEnd();
    glColor4f(0.0, 0.0, 0.0, 1.0);
    glBegin(GL_LINES); {
        glVertex3f(x - r    , y        , z + 0.01);
        glVertex3f(x - r    , y + r    , z + 0.01);
        glVertex3f(x - r    , y + r    , z + 0.01);
        glVertex3f(x - r / 3, y + r / 3, z + 0.01);
        glVertex3f(x - r / 3, y + r / 3, z + 0.01);
        glVertex3f(x        , y + r    , z + 0.01);
        glVertex3f(x        , y + r    , z + 0.01);
        glVertex3f(x + r / 3, y + r / 3, z + 0.01);
        glVertex3f(x + r / 3, y + r / 3, z + 0.01);
        glVertex3f(x + r    , y + r    , z + 0.01);
        glVertex3f(x + r    , y + r    , z + 0.01);
        glVertex3f(x + r    , y        , z + 0.01);
        glVertex3f(x + r    , y        , z + 0.01);
        glVertex3f(x - r    , y        , z + 0.01);
    } glEnd();
}

double dist(double x0, double y0, double x1, double y1) {
    return sqrt(sqr(x1 - x0) + sqr(y1 - y0));
}

void drawSword(double x0, double y0, double x1, double y1, double color, double z) {
    glColor4f(color, color, color, 1.0);
    glBegin(GL_LINES); {
        glVertex3f(x0, y0, z);
        glVertex3f(x1, y1, z);

        double x = x0 + (x1 - x0) * 0.2;
        double y = y0 + (y1 - y0) * 0.2;
        double vx = - y1 + y0;
        double vy = x1 - x0;

        glVertex3f(x - vx * 0.1, y - vy * 0.1, z);
        glVertex3f(x + vx * 0.1, y + vy * 0.1, z);
    } glEnd();

    double len = dist(x0, y0, x1, y1);

    double ncolor = 1.0 - color;
    glColor4f(ncolor, ncolor, ncolor, 1.0);
    glBegin(GL_LINES); {
        double x = x0 + (x1 - x0) * 0.2;
        double y = y0 + (y1 - y0) * 0.2;
        glVertex3f(x, y - len * 0.01, z);
        glVertex3f(x1, y1 - len * 0.01, z);
    } glEnd();

}