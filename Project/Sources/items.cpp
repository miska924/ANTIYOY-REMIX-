#include <bits/stdc++.h>
#include <GL/glut.h>
#include "globals.h"
#include "items.h"
#include "primitives.h"

using namespace std;

void drawPERSON1(double x, double y, double r) {
    drawCircle(x, y, r / 2         , 1, 0.1);
    drawCircleEmpty(x, y, (r / 2)  , 0, 0.2);
    drawCircle(x - r / 6, y, r / 12, 0, 0.2);
    drawCircle(x + r / 6, y, r / 12, 0, 0.2);
}

void drawPERSON2(double x, double y, double r) {
    drawPERSON1(x, y, r);
    double s = sqrt(2) / 2;
    drawSword(x + r * s, y + r * s, x - r * s, y - r * s);
}

void drawPERSON3(double x, double y, double r) {
    drawPERSON1(x, y, r);
    double s = sqrt(2) / 2;
    drawSword(x + r * s, y + r * s, x - r * s, y - r * s);
    drawSword(x - r * s, y + r * s, x + r * s, y - r * s);
}

void drawPERSON4(double x, double y, double r) {
    drawPERSON3(x, y, r);
    drawCrown(x, y + r * 2 / 3, r / 4, 0.1);
}

void drawCITADEL(double x, double y, double r) {
    drawSquare(x, y, r, 1);
}

void drawTOWER1(double x, double y, double r) {
    drawSquare(x, y, r, 1);
}

void drawTOWER2(double x, double y, double r) {
    drawSquare(x, y, r, 1);
}

void drawFARM(double x, double y, double r) {
    drawSquare(x, y, r, 1);
}

void drawTREE(double x, double y, double r) {
    drawSquare(x, y, r, 1);
}

void drawTOMB(double x, double y, double r) {
    drawSquare(x, y, r, 1);
}

void drawItem(int item, double x, double y, double r) {
    switch(item) {
        case PERSON1: 
            drawPERSON1(x, y, r);
            break;
        case PERSON2: 
            drawPERSON2(x, y, r);
            break;
        case PERSON3: 
            drawPERSON3(x, y, r);
            break;
        case PERSON4: 
            drawPERSON4(x, y, r);
            break;
        case CITADEL:
            drawCITADEL(x, y, r);
            break;
        case TOWER1:
            drawTOWER1(x, y, r);
            break;
        case TOWER2:
            drawTOWER2(x, y, r);
            break;
        case FARM:
            drawFARM(x, y, r);
            break;
        case TREE:
            drawTREE(x, y, r);
            break;
        case TOMB:
            drawTOMB(x, y, r);
            break;
    }
}