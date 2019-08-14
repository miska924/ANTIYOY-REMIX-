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
    double x = getx(i, j);
    double y = gety(i, j);
    double r0 = 2.0 / sqrtl(3);
    if (xl > x - r0) {
        DEBUGX = i;
        DEBUGY = j;
    }
    xl = min(xl, x - r0);
    xr = max(xr, x + r0);
    yl = min(yl, y - 1);
    yr = max(yr, y + 1);
}

void makeUp(int i, int j) {
    updateXY(i, j);
    field[i][j].mark = TMP;
    field[i][j].color = EMPTY;
    if (chance() < FORESTY) {
        field[i][j].item = TREE;
    } else {
        field[i][j].item = EMPTY;
    }
}

void genSkelet(int need) {
    int i = BEGIN, j = BEGIN;
    while (int(tiles.size()) < need) {
        if (!exist(i, j)) {
            makeUp(i, j);
            tiles.push_back(pair<int, int>{i, j});
        }
        int dx = 1, dy = 1;
        while (dx * dy == 1) {
            dx = rand() % 3 - 1;
            dy = rand() % 3 - 1;
        }
        i += dx;
        j += dy;
    }
}

void genMuscul(int need) {
    random_shuffle(tiles.begin(), tiles.end());
    for (int i = 0; i < int(tiles.size()); ++i) {
        int x = tiles[i].first;
        int y = tiles[i].second;
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if (dx * dy != 1 && !exist(x + dx, y + dy) && int(tiles.size()) < need) {
                    tiles.push_back(pair<int, int>{x + dx, y + dy});
                    makeUp(x + dx, y + dy);
                }
            }
        }
    }
}

void paint(pair<int, int> begin, int color, int need) {
    TMP++;
    vector<pair<int, int> > q(1, begin);
    field[begin.first][begin.second].color = color;
    for (int i = 0; i < need && i < int(q.size()); ++i) {
        random_shuffle(q.begin() + i, q.end());
        int x = q[i].first;
        int y = q[i].second;
        field[x][y].mark = TMP;
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if (dx * dy != 1 && (dx != 0 || dy != 0) &&
                    field[x + dx][y + dy].color == EMPTY) {
                    field[x + dx][y + dy].color = color;
                    q.push_back(pair<int, int>{x + dx, y + dy});
                }
            }
        }
    }
    for (int i = need; i < int(q.size()); ++i) {
        int x = q[i].first;
        int y = q[i].second;
        field[x][y].color = EMPTY;
    }
}

int check() {
    vector<int> pl(PLAYERS, 0);
    int ans = 2;
    for (int i = 0; i < int(tiles.size()); ++i) {
        int x = tiles[i].first;
        int y = tiles[i].second;
        if (field[x][y].color != EMPTY) {
            pl[field[x][y].color - 1]++;
        }
        if (field[x][y].color != EMPTY) {
            int cnt = 0;
            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    if (dx * dy != 1 && (dx != 0 || dy != 0)) {
                        if (field[x][y].color == field[x + dx][y + dy].color) {
                            if (field[x][y].mark != field[x + dx][y + dy].mark) {
                                ans = 1;
                                // cerr << "!" << endl;
                            }
                            cnt++;
                        } else if (field[x + dx][y + dy].color != EMPTY &&
                                   field[x + dx][y + dy].color != VOID) {
                            // cerr << field[x][y].color << ":" << field[x + dx][y + dy].color << endl;
                            ans = 1;
                        }
                    }
                }
            }
            if (cnt == 0) {
                return 0;
            }
        }
    }
    sort(pl.begin(), pl.end());
    if (double(pl.front()) / pl.back() < 0.75) {
        return 0;
    }
    return ans;
}

void GenerateField() {
    int ok = 0;
    int it = 0;
    int CNT = 2000;

    WHO = 1;
    MODE = WORLD;
    
    for (int i = 0; i < 10; ++i) {
        buttons[i].item = EMPTY;
        buttons[i].color = VOID;
        buttons[i].state = 0;
    }
    buttons[9].color = WHO % PLAYERS + 1;
    while ((ok + it * 2 / CNT) < 2 && ++it < CNT) {
        SCALE = 1;
        X0 = Y0 = 0;
        TMP = 0;
        xl = yl = INF;
        xr = yr = -INF;
        X0 = Y0 = 0;
        tiles.clear();
        for (int i = 0; i < MAX; ++i) {
            for (int j = 0; j < MAX; ++j) {
                field[i][j].color = VOID;
                field[i][j].mark = 0;
                field[i][j].state = 0;
            }
        }
        genSkelet(FSZ / 2);
        genMuscul(FSZ);

        double xlen = xr - xl;
        double ylen = yr - yl;
        SCALE = SZ * 0.8 / max(xlen, ylen);
        X0 = (xl + xr) / 2 - SZ / 2.0 / SCALE;
        Y0 = (yl + yr) / 2 - SZ / 2.0 / SCALE;
        int cnt = max(1, FSZ / PLAYERS / 20);

        vector<int> players(PLAYERS);
        for (int i = 0; i < PLAYERS; ++i) {
            players[i] = i + 1;
        }

        for (int i = 0; i < cnt; ++i) {
            random_shuffle(players.begin(), players.end());
            for (int j = 0; j < int(players.size()); ++j) {
                random_shuffle(tiles.begin(), tiles.end());
                for (int k = 0; k < int(tiles.size()); ++k) {
                    if (field[tiles[k].first][tiles[k].second].color == EMPTY) {
                        paint(tiles[k], players[j], rand() % 2 + 4);
                        break;
                    }
                }
            }
        }
        // cout << "#" << endl;
        ok = check();
        // cout << ok << endl;
    }
    if (ok == 0) {
        cerr << "BAD MAP" << endl;
    } else if (ok == 2) {
        cerr << "GOOD MAP" << endl;
    } else {
        cout << "SO-SO" << endl;
    }
    refresh();
}

void pool(int x, int y, vector<pair<int, int> > &p, vector<pair<int, int> > &cs) {
    field[x][y].mark = TMP;
    p.push_back(pair<int, int>{x, y});
    if (field[x][y].item == CITADEL) {
        cs.push_back(pair<int, int>{x, y});
    }
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx * dy != 1 && field[x + dx][y + dy].mark != TMP
                             && field[x + dx][y + dy].color == field[x][y].color) {
                pool(x + dx, y + dy, p, cs);
            }
        }
    }
}

void refresh() {
    TMP++;
    for (int i = 0; i < int(tiles.size()); ++i) {
        int x = tiles[i].first;
        int y = tiles[i].second;
        if (field[x][y].mark != TMP) {
            vector<pair<int, int> > cur;
            vector<pair<int, int> > cs;
            pool(x, y, cur, cs);
            if (field[x][y].color == EMPTY) {
                for (int i = 0; i < int(cur.size()); ++i) {
                    if (field[cur[i].first][cur[i].second].item == CITADEL) {
                        makeUp(cur[i].first, cur[i].second);
                    }
                }
            } else if (int(cur.size()) == 1) {
                if (field[x][y].item == CITADEL) {
                    field[x][y].item = EMPTY;
                }
            } else {
                if (int(cs.size()) > 1) {
                    int root = rand() % int(cs.size());
                    for (int i = 0; i < int(cs.size()); ++i) {
                        if (i != root) {
                            field[cs[i].first][cs[i].second].item = EMPTY;
                        }
                    }
                } else if (int(cs.size()) == 0) {
                    random_shuffle(cur.begin(), cur.end());
                    for (int i = 0; i < int(cur.size()); ++i) {
                        if (field[cur[i].first][cur[i].second].item == EMPTY) {
                            field[cur[i].first][cur[i].second].item = CITADEL;
                            cs.push_back(cur[i]);
                            break;
                        }
                    }
                    if (cs.empty()) {
                        int root = rand() % int(cur.size());
                        field[cur[root].first][cur[root].second].item = CITADEL;
                    }
                }
            }
        }
    }
}