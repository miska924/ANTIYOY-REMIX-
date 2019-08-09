#include <bits/stdc++.h>
#include "globals.h"

tile field[MAX][MAX];
double MSX;
double MSY;
int MSI;
int MSJ;
double SCALE;
double X0;
double Y0;
int FSZ;
int PLAYERS;
int WHO;

double getx(int i, int j) {
    return (sqrt(3) * i - X0) * SCALE;
}

double gety(int i, int j) {
    return (2.0 * j + i - Y0) * SCALE;
}