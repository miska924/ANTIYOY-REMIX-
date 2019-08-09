#include <bits/stdc++.h>
#include <GL/glut.h>

using namespace std;

typedef double ld;

struct tile {
    int color;
    int item;
    int def = 0;

    int used;
    int state = 0;
};

vector<vector<ld> > cl = {{1.0, 0.9, 0.6},
                          {1.0, 0.0, 0.0},
                          {0.0, 0.0, 1.0},
                          {0.0, 1.0, 0.0},
                          {1.0, 1.0, 0.0},
                          {0.0, 1.0, 1.0},
                          {1.0, 0.0, 1.0}};

const ld EPS = 1e-9;
const ld SZ = 20.0;
const int WSZ = 600;
const ld INF = 1e18;

const int MAX = 10000;
tile field[MAX][MAX];

ld xl = INF;
ld xr = -INF;
ld yl = INF;
ld yr = -INF;

ld x_0 = 0;
ld y_0 = 0;
ld scale = 1;

int sz;
int pl;

int i_0 = MAX / 2, j_0 = MAX / 2, u = 1;

int curx = 0, cury = 0;
ld mx = 0, my = 0;

double getx(int i, int j) {
    return (sqrtl(3) * i - x_0) * scale;
}

double gety(int i, int j) {
    return (2.0 * j + i - y_0) * scale;
}

ld ang(int x) {
    return ld(x) * M_PI / 180;
}

void draw_tile(int i, int j) {
    ld x = getx(i, j);
    ld y = gety(i, j);
    ld r0 = 2.0 / sqrtl(3);

    ld k = 0.9 + 0.1 * field[i][j].state;
    ld q = 0.2;

    int player = field[i][j].color;
    glColor4f(cl[player][0], cl[player][1], cl[player][2], 1.0);

    glBegin(GL_POLYGON); {
        glVertex2f(x - r0 / 2 * k * scale, y - k * scale);
        glVertex2f(x + r0 / 2 * k * scale, y - k * scale);
        glVertex2f(x + r0     * k * scale, y            );
        glVertex2f(x + r0 / 2 * k * scale, y + k * scale);
        glVertex2f(x - r0 / 2 * k * scale, y + k * scale);
        glVertex2f(x - r0     * k * scale, y            );
    } glEnd();

    // glColor4f(1.0 - cl[player][0], 1.0 - cl[player][1], 1.0 - cl[player][2], 1.0);
    // for (int d = 0; d < field[i][j].def; ++d) {
    //     glBegin(GL_LINES); {
    //         glVertex3f(x - r0 / 2 * k * scale * (0.95 - q * d), y - k * scale * (0.95 - q * d), 0.1);
    //         glVertex3f(x + r0 / 2 * k * scale * (0.95 - q * d), y - k * scale * (0.95 - q * d), 0.1);

    //         glVertex3f(x + r0 / 2 * k * scale * (0.95 - q * d), y - k * scale * (0.95 - q * d), 0.1);
    //         glVertex3f(x + r0     * k * scale * (0.95 - q * d), y                            , 0.1);

    //         glVertex3f(x + r0     * k * scale * (0.95 - q * d), y                            , 0.1);
    //         glVertex3f(x + r0 / 2 * k * scale * (0.95 - q * d), y + k * scale * (0.95 - q * d), 0.1);

    //         glVertex3f(x + r0 / 2 * k * scale * (0.95 - q * d), y + k * scale * (0.95 - q * d), 0.1);
    //         glVertex3f(x - r0 / 2 * k * scale * (0.95 - q * d), y + k * scale * (0.95 - q * d), 0.1);

    //         glVertex3f(x - r0 / 2 * k * scale * (0.95 - q * d), y + k * scale * (0.95 - q * d), 0.1);
    //         glVertex3f(x - r0     * k * scale * (0.95 - q * d), y                            , 0.1);

    //         glVertex3f(x - r0     * k * scale * (0.95 - q * d), y                            , 0.1);
    //         glVertex3f(x - r0 / 2 * k * scale * (0.95 - q * d), y - k * scale * (0.95 - q * d), 0.1);
    //     } glEnd();
    // }

    switch(field[i][j].item) {
        case 1:
            for (int i = 0; i < 360; i += 20) {
                glColor4f(0, 0, 0, 0);
                glBegin(GL_LINES); {
                    glVertex3f(x + (k / 2) * scale * sin(ang(i    )),
                               y + (k / 2) * scale * cos(ang(i    )), 0.1);
                    glVertex3f(x + (k / 2) * scale * sin(ang(i + 20)),
                               y + (k / 2) * scale * cos(ang(i + 20)), 0.1);
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
                glVertex3f(x - (k / 2) * scale, y - (k / 2) * scale, 0.1);
                glVertex3f(x + (k / 2) * scale, y + (k / 2) * scale, 0.1);

                glVertex3f(x - (k / 2) * scale, y + (k / 2) * scale, 0.1);
                glVertex3f(x + (k / 2) * scale, y - (k / 2) * scale, 0.1);
            } glEnd();
            break;
    }
}

void draw_dfs(int i, int j) {
    draw_tile(i, j);
    field[i][j].used = u;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx * dy != 1 && field[i + dx][j + dy].color != -1
                             && field[i + dx][j + dy].used != u) {
                draw_dfs(i + dx, j + dy);
            }
        }
    }
}

void draw_field() {
    u++;
    draw_dfs(i_0, j_0);
}

void Draw() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    draw_field();
    
    glFlush();
    glutSwapBuffers();
}

void Timer(int value) {
    Draw();
    glutTimerFunc(50, Timer, 1);
}

void Initialize() {
    glClearColor(0.5, 0.7, 0.8, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, SZ, 0.0, SZ, -1.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
}

bool exist(int i, int j) {
    return field[i][j].color != -1;
}

void set_pos(int i, int j) {
    field[i][j].used = u;

    ld x = sqrtl(3) * i;
    ld y = 2.0 * j + i;
    ld r0 = 2.0 / sqrtl(3);

    xl = min(xl, x - r0);
    xr = max(xr, x + r0);
    yl = min(yl, y - 1);
    yr = max(yr, y + 1);

    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx * dy != 1 && exist(i + dx, j + dy)
                && field[i + dx][j + dy].used != u) {
                set_pos(i + dx, j + dy);
            }
        }
    }
}

void make_up(int i, int j) {
    field[i][j].color = 0;
    if (rand() % 10 == 0) {
        field[i][j].item = 1;
    } else {
        field[i][j].item = 8 * int(rand() % 10 == 0);
    }
    field[i][j].used = 0;
    // field[i][j].def = rand() % 4;
}

void bfs_make(vector<pair<int, int> > &vec, int sz) {
    for (int i = 0; i < vec.size(); ++i) {
        pair<int, int> p = vec[i];
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if (dx * dy == 1 || exist(p.first + dx, p.second + dy)) {
                    continue;
                }
                vec.push_back(pair<int, int>{p.first + dx, p.second + dy});
                if (vec.size() >= sz) {
                    return;
                }
                make_up(p.first + dx, p.second + dy);
            }
        }
    }
}

void gen_dfs(int i, int j, vector<pair<int, int> > &f, int sz) {
    if (f.size() >= sz) {
        return;
    }
    if (!exist(i, j)) {
        make_up(i, j);
        f.push_back(pair<int, int>{i, j});
    }
    while (f.size() < sz) {
        int dx = rand() % 3 - 1;
        int dy = rand() % 3 - 1;
        if (dx * dy != 1) {
            gen_dfs(i + dx, j + dy, f, sz);
        }
    }
}

void paint(int x, int y, int col, vector<pair<int, int> > &f, int need) {
    if (f.size() >= need || field[x][y].color != 0) {
        return;
    }
    if (field[x][y].color == 0) {
        f.push_back(pair<int, int>{x, y});
        field[x][y].color = col;
    }
    vector<pair<int, int> > to;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx * dy != 1 && exist(x + dx, y + dy)) {
                to.push_back(pair<int, int>{x + dx, y + dy});
            }
        }
    }
    random_shuffle(to.begin(), to.end());
    for (int i = 0; i < to.size() && f.size() < need; ++i) {
        paint(to[i].first, to[i].second, col, f, need);
    }
}

void generate_field() {
    vector<pair<int, int> > f;
    u++;
    gen_dfs(i_0, j_0, f, max(1, sz / 2));
    bfs_make(f, sz);
    int need = max(1, sz / pl / 15);
    cout << need << endl;
    for (int i = 0; i < pl; ++i) {
        for (int j = 0; j < need; ++j) {
            int cur = rand() % f.size();
            while (field[f[cur].first][f[cur].second].color != 0) {
                cur = rand() % f.size();
            }
            vector<pair<int, int> > vec;
            paint(f[cur].first, f[cur].second, i + 1, vec, (rand() % 3) + 3);
        }
    } 
}

void make_field() {
    for (int i = 0; i < MAX; ++i) {
        for (int j = 0; j < MAX; ++j) {
            field[i][j].color = -1; //means that there is no tile
        }
    }
    generate_field();
    u++;
    set_pos(i_0, j_0);
    ld xlen = xr - xl;
    ld ylen = yr - yl;
    scale = SZ * 0.8 / max(xlen, ylen);
    x_0 = (xl + xr) / 2 - SZ / 2 / scale;
    y_0 = (yl + yr) / 2 - SZ / 2 / scale;
}

ld sqr(ld x) {
    return x * x;
}

ld ms_dist(int x, int y) {
    return sqrt(sqr(getx(x, y) - mx) + sqr(gety(x, y) - my));
}

void find_mouse(int x, int y) {
    ld dist = ms_dist(x, y);
    int mnx = x, mny = y;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx * dy != 1) {
                if (ms_dist(x + dx, y + dy) < dist) {
                    dist = ms_dist(x + dx, y + dy);
                    mnx = x + dx;
                    mny = y + dy;
                }
            }
        }
    }
    if (mnx == x && mny == y) {
        curx = mnx;
        cury = mny;
        return;
    }
    find_mouse(mnx, mny);
}

void MouseMove(int x, int y) {

    field[curx][cury].state = 0;
    mx = ld(x) / WSZ * SZ;
    my = SZ - ld(y) / WSZ * SZ;
    find_mouse(0, 0);
    field[curx][cury].state = 1;

    string message = string("MouseMove: ") + to_string(mx) + " " + to_string(my);
    glutSetWindowTitle(message.c_str());
}

void MousePressed(int button, int state, int x, int y) {
    glutSetWindowTitle("MousePressed");
}

void MousePressedMove(int x, int y) {
    field[curx][cury].state = 0;
    mx = ld(x) / WSZ * SZ;
    my = SZ - ld(y) / WSZ * SZ;
    find_mouse(0, 0);
    field[curx][cury].state = 1;
    glutSetWindowTitle("MousePressedMove");
}

int main(int argc, char** argv) {
    // srand(time(NULL));
    srand(641585);
    cout << "field & players" << endl;
    cin >> sz >> pl;
    // sz = 40;
    // pl = 2;
    make_field();
    int lol = 0;
    char** kek;
    glutInit(&lol, kek);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WSZ, WSZ);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("PRIVIT");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(Draw);

    glutMotionFunc(MousePressedMove);
    glutPassiveMotionFunc(MouseMove);
    glutMouseFunc(MousePressed);

    glutTimerFunc(50, Timer, 0);
    Initialize();
    glutMainLoop();
    return 0;
}