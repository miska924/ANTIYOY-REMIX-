#include <bits/stdc++.h>
#include "globals.h"

using namespace std;

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
int MODE;

int DEBUGX, DEBUGY;

int TMP = 0;

int CURBUY;
int CURMOVEI;
int CURMOVEJ;

vector<pair<int, int> > tiles;
vector<vector<double> > CL = {{0.7, 0.7, 0.7},//{{1.0, 0.9, 0.6},
                          {1.0, 0.0, 0.0},
                          {0.0, 0.0, 1.0},
                          {0.0, 1.0, 0.0},
                          {1.0, 1.0, 0.0},
                          {0.0, 1.0, 1.0},
                          {1.0, 0.0, 1.0}};

double getx(int i, int j) {
    return (sqrtl(3) * i - X0) * SCALE;
}

double gety(int i, int j) {
    return (2.0 * j + double(i) - Y0) * SCALE;
}

tile buttons[BUTTONS];

int button() {
    if (MSY > SZ / 10) {
        return -1;
    } else {
        int ans = int(MSX / (SZ / 10));
        if (ans != NEXT_TURN && MODE == WORLD) {
            return -1;
        }
        return ans;
    }
}

double ang(int x) {
    return double(x) * M_PI / 180;
}

double sqr(double x) {
    return x * x;
}