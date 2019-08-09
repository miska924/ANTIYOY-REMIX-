#include <bits/stdc++.h>

using namespace std;

#include "globals.h"
#include "generate.h"

double xl = INF, xr = -INF, yl = INF, yr = -INF;

bool exist(int i, int j) {
    return field[i][j].color != VOID;
}

double chance() {
    return double(rand() % 1001) / 1000;
}

void updateXY(int i, int j) {
    double x = sqrtl(3) * i;
    double y = 2.0 * j + i;
    double r0 = 2.0 / sqrtl(3);

    xl = min(xl, x - r0);
    xr = max(xr, x + r0);
    yl = min(yl, y - 1);
    yr = max(yr, y + 1);
}

void makeUp(int i, int j) {
    updateXY(i, j);
    field[i][j].color = EMPTY;
    if (chance() < FORESTY) {
        field[i][j].item = TREE;
    } else {
        field[i][j].item  = EMPTY;
    }
}

void genSkelet(vector<pair<int, int> > &t, int need) {
    int i = BEGIN, j = BEGIN;
    while (t.size() < need) {
        if (!exist(i, j)) {
            makeUp(i, j);
            t.push_back(pair<int, int>{i, j});
        }
        int dx = 1, dy = 1;
        while (dx * dy == 1) {
            dx = rand() % 3 - 1;
            dy = rand() % 3 - 1;
        }
        i += dx;
        j += dy;
    }
    cerr << "SKELET IS GENERATED" << endl;
}

void genMuscul(vector<pair<int, int> > t, int need) {
    random_shuffle(t.begin(), t.end());
    for (int i = 0; i < t.size(); ++i) {
        int x = t[i].first;
        int y = t[i].second;
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if (dx * dy != 1 && !exist(x + dx, y + dy) && t.size() < need) {
                    t.push_back(pair<int, int>{x + dx, y + dy});
                    makeUp(x + dx, y + dy);
                }
            }
        }
    }
    cerr << "MUSCUL IS GENERATED" << endl;
}

void paint(pair<int, int> begin, int color, int need) {
    int i = begin.first, j = begin.second;
    for (int cur = 0, p = 0; cur < need && p < need * 2; ++cur, ++p) {
        field[i][j].color = color;
        int dx = 1, dy = 1;
        while (dx * dy == 1) {
            dx = rand() % 3 - 1;
            dy = rand() % 3 - 1;
        }
        if (field[i + dx][j + dy].color == EMPTY) {
            i += dx;
            j += dy;
        } else {
            cur--;
        }
    }
    cerr << ">> BASE IS GENERATED. COLOR " << color << endl;
}

void GenerateField() {
    for (int i = 0; i < MAX; ++i) {
        for (int j = 0; j < MAX; ++j) {
            field[i][j].color = VOID;
        }
    }
    vector<pair<int, int> > t;
    genSkelet(t, FSZ / 2);
    genMuscul(t, FSZ);

    double xlen = xr - xl;
    double ylen = yr - yl;
    SCALE = SZ * 0.8 / max(xlen, ylen);
    X0 = (xl + xr) / 2 - SZ / 2 / SCALE;
    Y0 = (yl + yr) / 2 - SZ / 2 / SCALE;

    cerr << "WORLD IS GENERATED" << endl;

    int cnt = FSZ / PLAYERS / 20;

    vector<int> players(PLAYERS);
    for (int i = 0; i < PLAYERS; ++i) {
        players[i] = i + 1;
    }

    for (int i = 0; i < cnt; ++i) {
        random_shuffle(players.begin(), players.end());
        for (int j = 0; j < players.size(); ++j) {
            int cur = rand() % t.size();
            while (field[t[cur].first][t[cur].second].color != EMPTY) {
                cur = rand() % t.size();
            }
            paint(t[cur], players[j], rand() % 5 + 2);
        }
    }
}