#include <bits/stdc++.h>
#include <GL/glut.h>
#include "globals.h"
#include "field.h"

double ang(int x) {
    return double(x) * M_PI / 180;
}

void drawTile(int i, int j) {
    double x = getx(i, j);
    double y = gety(i, j);
    double r0 = 2.0 / sqrtl(3);

    double k = 0.9 + 0.1 * field[i][j].state;
    // double q = 0.2;

    int player = field[i][j].color;
    glColor4f(CL[player][0], CL[player][1], CL[player][2], 1.0);

    glBegin(GL_POLYGON); {
        glVertex2f(x - r0 / 2 * k * SCALE, y - k * SCALE);
        glVertex2f(x + r0 / 2 * k * SCALE, y - k * SCALE);
        glVertex2f(x + r0     * k * SCALE, y            );
        glVertex2f(x + r0 / 2 * k * SCALE, y + k * SCALE);
        glVertex2f(x - r0 / 2 * k * SCALE, y + k * SCALE);
        glVertex2f(x - r0     * k * SCALE, y            );
    } glEnd();

    // glColor4f(1.0 - CL[player][0], 1.0 - CL[player][1], 1.0 - CL[player][2], 1.0);
    // for (int d = 0; d < field[i][j].def; ++d) {
    //     glBegin(GL_LINES); {
    //         glVertex3f(x - r0 / 2 * k * SCALE * (0.95 - q * d), y - k * SCALE * (0.95 - q * d), 0.1);
    //         glVertex3f(x + r0 / 2 * k * SCALE * (0.95 - q * d), y - k * SCALE * (0.95 - q * d), 0.1);

    //         glVertex3f(x + r0 / 2 * k * SCALE * (0.95 - q * d), y - k * SCALE * (0.95 - q * d), 0.1);
    //         glVertex3f(x + r0     * k * SCALE * (0.95 - q * d), y                            , 0.1);

    //         glVertex3f(x + r0     * k * SCALE * (0.95 - q * d), y                            , 0.1);
    //         glVertex3f(x + r0 / 2 * k * SCALE * (0.95 - q * d), y + k * SCALE * (0.95 - q * d), 0.1);

    //         glVertex3f(x + r0 / 2 * k * SCALE * (0.95 - q * d), y + k * SCALE * (0.95 - q * d), 0.1);
    //         glVertex3f(x - r0 / 2 * k * SCALE * (0.95 - q * d), y + k * SCALE * (0.95 - q * d), 0.1);

    //         glVertex3f(x - r0 / 2 * k * SCALE * (0.95 - q * d), y + k * SCALE * (0.95 - q * d), 0.1);
    //         glVertex3f(x - r0     * k * SCALE * (0.95 - q * d), y                            , 0.1);

    //         glVertex3f(x - r0     * k * SCALE * (0.95 - q * d), y                            , 0.1);
    //         glVertex3f(x - r0 / 2 * k * SCALE * (0.95 - q * d), y - k * SCALE * (0.95 - q * d), 0.1);
    //     } glEnd();
    // }

    switch(field[i][j].item) {
        case 1:
            for (int i = 0; i < 360; i += 20) {
                glColor4f(0, 0, 0, 0);
                glBegin(GL_LINES); {
                    glVertex3f(x + (k / 2) * SCALE * sin(ang(i    )),
                               y + (k / 2) * SCALE * cos(ang(i    )), 0.1);
                    glVertex3f(x + (k / 2) * SCALE * sin(ang(i + 20)),
                               y + (k / 2) * SCALE * cos(ang(i + 20)), 0.1);
                } glEnd();
            }
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            glColor4f(0, 0, 0, 0);
            glBegin(GL_LINES); {
                glVertex3f(x - (k / 2) * SCALE, y - (k / 2) * SCALE, 0.1);
                glVertex3f(x + (k / 2) * SCALE, y + (k / 2) * SCALE, 0.1);

                glVertex3f(x - (k / 2) * SCALE, y + (k / 2) * SCALE, 0.1);
                glVertex3f(x + (k / 2) * SCALE, y - (k / 2) * SCALE, 0.1);
            } glEnd();
            break;
    }
}

void drawField() {
    for (int i = 0; i < tiles.size(); ++i) {
        drawTile(tiles[i].first, tiles[i].second);
    }
}