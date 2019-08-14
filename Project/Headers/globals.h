#ifndef GLOBALS
#define GLOBALS

const int VOID     =-1;

const int EMPTY    = 0;
const int PERSON   = 1;
const int TOWER    = 2;
const int CITADEL  = 3;
const int TREE     = 4;

struct tile {
    int color, item;
    int state = 0;
    int mark = 0; 
};

const int MAX = 1000;
const double SZ = 20.0;
const double BORDER = 0.01;
const int WSZ = 700;
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
extern int TMP;

extern int MODE;

const int WORLD = 0;
const int CITY  = 1;
const int BUY   = 2;
const int MOVE  = 3;

const double FORESTY = 0.1;

double getx(int i, int j);
double gety(int i, int j);

extern std::vector<std::pair<int, int> > tiles;
extern std::vector<std::vector<double> > CL;

extern int DEBUGX;
extern int DEBUGY;

const int NEXT_TURN = 9;
const int BUTTONS = 10;
extern tile buttons[BUTTONS];
int button();

#endif