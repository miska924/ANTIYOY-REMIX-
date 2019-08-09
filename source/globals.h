#ifndef GLOBALS
#define GLOBALS

const int VOID     =-1;

const int EMPTY    = 0;
const int JUMPING  = 1;
const int STANDING = 1;
const int TOWER    = 2;
const int CITADEL  = 3;
const int TREE     = 4;

struct tile {
    int color, item;
    int state = 0;  
};

const int MAX = 1000;
const int SZ = 20;
const int WSZ = 600;
const int BEGIN = 500;

const double INF = 1e18;

extern tile field[MAX][MAX];

extern double MSX;
extern double MSY;
extern int MSI;
extern int MSJ;

extern double SCALE;
extern double X0;
extern double Y0;

extern int FSZ;
extern int PLAYERS;
extern int WHO;

const double FORESTY = 0.1;

double getx(int i, int j);
double gety(int i, int j);

#endif