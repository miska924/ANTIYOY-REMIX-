#include <bits/stdc++.h>
#include <GL/glut.h>
#include "globals.h"
#include "interact.h"

using namespace std;

double sqr(double x) {
    return x * x;
}

double ms_dist(int x, int y) {
    return sqrt(sqr(getx(x, y) - MSX) + sqr(gety(x, y) - MSY));
}

void find_mouse(int x, int y) {
    while (true) {
        double dist = ms_dist(x, y);
        int mnx = x, mny = y;
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if (dx * dy != 1) {
                    if (ms_dist(x + dx, y + dy) < dist) {
                        dist = ms_dist(x + dx, y + dy);
                        mnx = x + dx;
                        mny = y + dy;
                    }
                }
            }
        }
        if (mnx == x && mny == y) {
            MSI = mnx;
            MSJ = mny;
            return;
        }
        x = mnx;
        y = mny;
    }
}

void MouseMove(int x, int y) {
    field[MSI][MSJ].state = 0;
    MSX = double(x) / WSZ * SZ;
    MSY = SZ - double(y) / WSZ * SZ;
    find_mouse(0, 0);
    field[MSI][MSJ].state = 1;

    string message = string("MouseMove: ") + to_string(MSX) + " " + to_string(MSY);
    glutSetWindowTitle(message.c_str());
}

void MousePressed(int button, int state, int x, int y) {
    glutSetWindowTitle("MousePressed");
}

void MousePressedMove(int x, int y) {
    field[MSI][MSJ].state = 0;
    MSX = double(x) / WSZ * SZ;
    MSY = SZ - double(y) / WSZ * SZ;
    find_mouse(0, 0);
    field[MSI][MSJ].state = 1;

    string message = string("MouseMove: ") + to_string(MSX) + " " + to_string(MSY);
    glutSetWindowTitle(message.c_str());
}