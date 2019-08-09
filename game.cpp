#include <bits/stdc++.h>
#include <GL/glut.h>

using namespace std;

typedef double ld;

struct tile {
    int color;
    int item;
    int used;
};

const ld EPS = 1e-9;
const ld SZ = 20.0;
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

void draw_tile(int i, int j) {
    ld x = sqrtl(3) * i;
    ld y = 2.0 * j + i;
    ld r0 = 2.0 / sqrtl(3);

    ld k = 0.9;
    if (field[i][j].color == 0) {
        glColor4f(1.0, 0.9, 0.6, 1.0);
    } else if (field[i][j].color == 1) {
        glColor4f(1.0, 0.0, 0.0, 1.0);
    } else if (field[i][j].color == 2) {
        glColor4f(0.0, 0.0, 1.0, 1.0);
    }
    glBegin(GL_POLYGON); {
        glVertex2f((x - x_0 - (r0 / 2) * k) * scale, (y - y_0 - k) * scale);
        glVertex2f((x - x_0 + (r0 / 2) * k) * scale, (y - y_0 - k) * scale);
        glVertex2f((x - x_0 + (r0    ) * k) * scale, (y - y_0    ) * scale);
        glVertex2f((x - x_0 + (r0 / 2) * k) * scale, (y - y_0 + k) * scale);
        glVertex2f((x - x_0 - (r0 / 2) * k) * scale, (y - y_0 + k) * scale);
        glVertex2f((x - x_0 - (r0    ) * k) * scale, (y - y_0    ) * scale);
    } glEnd();
    if (field[i][j].item == 1) {

    } else if (field[i][j].item == 2) {

    } else if (field[i][j].item == 3) {

    } else if (field[i][j].item == 4) {

    } else if (field[i][j].item == 5) {

    } else if (field[i][j].item == 6) {

    } else if (field[i][j].item == 7) {

    } else if (field[i][j].item == 8) {
        glColor4f(0, 0, 0, 0);
        glBegin(GL_LINES); {
            glVertex3f((x - x_0 - k / 2) * scale, (y - y_0 - k / 2) * scale, 0.1);
            glVertex3f((x - x_0 + k / 2) * scale, (y - y_0 + k / 2) * scale, 0.1);

            glVertex3f((x - x_0 - k / 2) * scale, (y - y_0 + k / 2) * scale, 0.1);
            glVertex3f((x - x_0 + k / 2) * scale, (y - y_0 - k / 2) * scale, 0.1);
        } glEnd();
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
    ld k = 0.9;

    xl = min(xl, x - r0 * k);
    xr = max(xr, x + r0 * k);
    yl = min(yl, y - k);
    yr = max(yr, y + k);

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
    field[i][j].item = 8 * int(rand() % 10 == 0);
    field[i][j].used = 0;
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

void generate_field() {
    vector<pair<int, int> > f;
    u++;
    gen_dfs(i_0, j_0, f, max(1, sz / 2));
    bfs_make(f, sz);
    for (int i = 0; i < pl; ++i) {
        int need = max(1, sz / pl / 10);
        for (int j = 0; j < need; ++j) {
            paint(f[rand() % f.size()], rand() % 3 + 4);
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

int main(int argc, char** argv) {
    srand(time(NULL));
    cout << "size of field     : ";
    cin >> sz;
    cout << "number of players : ";
    cin >> pl;
    make_field();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("PRIVIT");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(Draw);
    glutTimerFunc(50, Timer, 0);
    Initialize();
    glutMainLoop();
    return 0;
}