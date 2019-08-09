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
int MOD;
vector<pair<int, int> > tiles;
vector<vector<double> > CL = {{1.0, 0.9, 0.6},
                          {1.0, 0.0, 0.0},
                          {0.0, 0.0, 1.0},
                          {0.0, 1.0, 0.0},
                          {1.0, 1.0, 0.0},
                          {0.0, 1.0, 1.0},
                          {1.0, 0.0, 1.0}};

double getx(int i, int j) {
    return (sqrt(3) * i - X0) * SCALE;
}

double gety(int i, int j) {
    return (2.0 * j + double(i) - Y0) * SCALE;
}