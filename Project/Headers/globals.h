#ifndef GLOBALS
#define GLOBALS

// TILE ITEMS {

const  int    VOID     = -1;
const  int    EMPTY    = 0;
const  int    FARM     = 1;
const  int    TOMB     = 2;
const  int    CITADEL  = 3;
const  int    TREE     = 4;

const  int    PERSON1  = 5;
const  int    PERSON2  = 6;
const  int    PERSON3  = 7;
const  int    PERSON4  = 8; 

const  int    TOWER1   = 9;
const  int    TOWER2   = 10;

// } WINDOW SETTINGS {

const  int    MAX      = 1000;    // number of LINES and COLUMNS in field array
const  int    BEGIN    = MAX / 2; // LINE and COLUMN of begining tile
const  int    WSZ      = 900;     // size of window in pixels
const  double SZ       = 20.0;    // size of window in coordinates
const  double BORDER   = 0.01;    // part-size of colored border

// } BASIS {

const  double INF      = 1e18; // math infinity

struct tile {                  // structure of tile {
    int color, item;           // structure of tile
    int state = 0;             // structure of tile
    int mark = 0;              // structure of tile
};                             // structure of tile }

// } FIELD PARAMETERS {

extern tile   field[MAX][MAX]; // array of tiles

extern double SCALE;           // scale
extern double X0;              // X coord of vector offset
extern double Y0;              // Y coord of vector offset

// } MOUSE PARAMETERS {

extern double MSX; // X coord of cursor
extern double MSY; // Y coord of cursor

extern int    MSI; // LINE   of tile (in field[][]) under cursor
extern int    MSJ; // COLUMN of tile (in field[][]) under cursor

// } WINDOW MODE {

extern int    MODE;        // shows what is happening

const  int    WORLD   = 0; // When there is no selected City
const  int    CITY    = 1; // When city selected
const  int    BUY     = 2; // When selected item to buy
const  int    MOVE    = 3; // When selected item to move

// } GAMEPLAY SETTINGS {

extern int    FSZ;           // number of tiles in all field
extern int    PLAYERS;       // number of all players
extern int    WHO;           // shows whose turn is it (player #i => WHO == i)
const  double FORESTY = 0.1; // chance to spawn tree in each tile (when it is generation of field)

// } USEFUL FUNCTIONS {

double getx(int i, int j);  // returns X coord of tile #ij (field[i][j])
double gety(int i, int j);  // returns Y coord of tile #ij (field[i][j])
int    button();            // returns which button is selected (-1 when there is none of them)
double ang(int x);          // returns angle in radians when you gives degrees
double sqr(double x);       // returns x*x

extern std::vector<std::pair<int, int> > tiles; // there are all tiles (pair<int, int>{LINE, COLUMN})
extern std::vector<std::vector<double> > CL;    // there are colors for all what is going on

const  int    NEXT_TURN = 9;    // number of NEXT TURN button
const  int    BUTTONS   = 10;   // number of buttons
extern tile   buttons[BUTTONS]; // array of buttons

extern int    CURBUY;   // ID of Item which is selected to buy
extern int    CURMOVEI; // LINE of item which is selected to move 
extern int    CURMOVEJ; // COLUMN of item which is selected to move 

extern int DEBUGX; // DEBUG
extern int DEBUGY; // DEBUG

extern int    TMP; // is used for temporal needs

#endif