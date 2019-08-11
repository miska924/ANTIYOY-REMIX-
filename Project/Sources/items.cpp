#include <bits/stdc++.h>
#include <GL/glut.h>
#include "globals.h"
#include "items.h"
#include "primitives.h"

using namespace std;

void drawP1(double x, double y, double r) {
    drawCircle(x, y, r / 2         , 1, 0.1);
    drawCircleEmpty(x, y, (r / 2)  , 0, 0.2);
    drawCircle(x - r / 6, y, r / 12, 0, 0.2);
    drawCircle(x + r / 6, y, r / 12, 0, 0.2);
}

void drawP2(double x, double y, double r) {
    drawP1(x, y, r);
    double s = sqrt(2) / 2;
    drawSword(x + r * s, y + r * s, x - r * s, y - r * s);
}

void drawP3(double x, double y, double r) {
    drawP1(x, y, r);
    double s = sqrt(2) / 2;
    drawSword(x + r * s, y + r * s, x - r * s, y - r * s);
    drawSword(x - r * s, y + r * s, x + r * s, y - r * s);
}

void drawP4(double x, double y, double r) {
    drawP3(x, y, r);
    drawCrown(x, y + r * 2 / 3, r / 4, 0.1);
}

void drawItem(int item, double x, double y, double r) {
    switch(item) {
        case P1: drawP1(x, y, r);
            break;
        case P2: drawP2(x, y, r);
            break;
        case P3: drawP3(x, y, r);
            break;
        case P4: drawP4(x, y, r);
            break;
    }
}