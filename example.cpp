#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <GL/glut.h>
//#include <windows.h>
#include <time.h>
#include <stdlib.h>
#define glVertex2f(a, b) glVertex3f(a, b, 0)

using namespace std;

typedef double ld;
const ld EPS = 1e-9;

ld n, m;
int in, im;
int k;
vector<pair<ld, ld> > people;
pair<ld, ld> ans = {0, 0};

int population = 100;
ld rad = 0.17;
vector<pair<ld, ld> > ind(population);
vector<ld> p(population);

ld scale;
ld scalez;
ld scalex;

ld rx() {
    return ld(rand() % in) + ld(rand() % (int(1e6) + 1)) / ld(1e6);
}

ld ry() {
    return ld(rand() % im) + ld(rand() % (int(1e6) + 1)) / ld(1e6);
}

ld f(pair<ld, ld> p) {
    ld mx = 1e18;
    for (int i = 0; i < k; ++i) {
        ld a = (p.first - people[i].first);
        ld b = (p.second - people[i].second);
        if (mx > a * a + b * b) {
            mx = a * a + b * b;
        }
    }
    return mx * mx * mx * mx;
}

pair<ld, ld> get_son(pair<ld, ld> a, pair<ld, ld> b) {
    pair<ld, ld> ans = {a.first, b.second};
    if (rand() % 2) ans = {b.first, a.second};
    if (ld(rand() % 1000) / 1000.0 < rad) ans.first = rx();
    if (ld(rand() % 1000) / 1000.0 < rad) ans.second = ry();
    return ans;
}

void change_pop() {
    ld sum = 0;
    for (int j = 0; j < population; ++j) {
        p[j] = f(ind[j]);
        sum += p[j];
    }
    ld now = 0;
    for (int j = 0; j < population; ++j) p[j] = (now += p[j] / sum);
    vector<pair<ld, ld> > nxt(population);
    for (int j = 0; j < population; ++j) {
        int a = upper_bound(p.begin(), p.end(), ld(rand() % int(1e3)) / ld(1e3)) - p.begin();
        int b = upper_bound(p.begin(), p.end(), ld(rand() % int(1e3)) / ld(1e3)) - p.begin();
        nxt[j] = get_son(ind[a], ind[b]);
        if (f(ans) < f(nxt[j])) {
            ans = nxt[j];
        }
    }
    ind = nxt;
}

bool comp(pair<ld, ld> a, pair<ld, ld> b) {
    return f(a) < f(b);
}

double ang = 0;
ld mx;
bool flag;
bool poligones;

void Draw() {
    ang++;
    bool lol = false;
    if (ang > 360) {
        ang -= 360;
        lol = true;
    }

    //if (int(ang) % 10 == 0)
    for (int i = 0; i < min(100, int(ang * 3 + 10)); ++i) change_pop();
    sort(ind.rbegin(), ind.rend(), comp);

    /*for (int i = 0; i < ind.size(); ++i) {
    res.push_back(ind[i]);
    }
    sort(res.rbegin(), res.rend(), comp);
    unique(res.begin(), res.end());
    res.resize(10);*/

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    //gluPerspective(100, 1800.0 / 1200.0, 0.00001, 1000000);
    /////glPushMatrix();

    glRotatef(-30, 1.0, 0.0, 0.0);
    //glScalef( 0.001, 0.001, 0.001 );
    glRotatef(ang, 0.0, 0.0, 1.0);
    //gluPerspective(30, 1800.0 / 1200.0, 0, 2000);
    //glFrustum( -100, 100, -100, 100, -100, 100);
    //gluPerspective(90, 1, 10, 100);
    //glRotatef(-30, 1.0, 0.0, 0.0);
    //glScalef( 2.0, 2.0, 0.0 );


    glBegin(GL_LINES);{
        for (ld x = (-n / 2.0) * scale; (x - (n / 2.0) * scale) < EPS; x += scalex) {
            for (ld y = (-m / 2.0) * scale; (y - (m / 2.0) * scale) < EPS; y += scalex) {
                if (y + scalex <= (m / 2.0) * scale + EPS && (abs(x - (-n / 2.0) * scale) < EPS || abs(x - (n / 2.0) * scale) < EPS)) {
                    glColor3f(1, 1, 1);
                    glVertex3f(x, y, 0);
                    glVertex3f(x, y + scalex, 0);
                }
                if (x + scalex <= (n / 2.0) * scale + EPS && (abs(y - (-m / 2.0) * scale) < EPS || abs(y - (m / 2.0) * scale) < EPS)) {
                    glColor3f(1, 1, 1);
                    glVertex3f(x, y, 0);
                    glVertex3f(x + scalex, y, 0);
                }
                ld kek = f({x / scale + n / 2, y / scale + m / 2}) / mx * 0.5;
                kek = kek + 0.03;
                glColor3f(kek, kek, kek);
                if (y + scalex <= (m / 2.0) * scale + EPS) {
                    if (abs(x - (-n / 2.0) * scale) < EPS || abs(x - (n / 2.0) * scale) < EPS) glColor3f(1, 1, 1);
                    glVertex3f(x, y, f({x / scale + n / 2, y / scale + m / 2}) * scalez);
                    glVertex3f(x, y + scalex, f({(x) / scale + n / 2, (y + scalex) / scale + m / 2}) * scalez);
                }
                glColor3f(kek, kek, kek);
                if (x + scalex <= (n / 2.0) * scale + EPS) {
                    if (abs(y - (-m / 2.0) * scale) < EPS || abs(y - (m / 2.0) * scale) < EPS) glColor3f(1, 1, 1);
                    glVertex3f(x, y, f({x / scale + n / 2, y / scale + m / 2}) * scalez);
                    glVertex3f(x + scalex, y, f({(x + scalex) / scale + n / 2, (y) / scale + m / 2}) * scalez);
                }
                glEnd();glBegin(GL_TRIANGLES);
                if (poligones) {  
                    if (x + scalex <= (n / 2.0) * scale + EPS && y + scalex <= (m / 2.0) * scale + EPS) {
                        glColor3f(kek + 0.05, kek + 0.05, kek + 0.05);
                        
                        if (f({x / scale + n / 2, y / scale + m / 2}) + f({(x + scalex) / scale + n / 2, (y + scalex) / scale + m / 2}) >
                            f({(x) / scale + n / 2, (y + scalex) / scale + m / 2}) + f({(x + scalex) / scale + n / 2, (y) / scale + m / 2})) {

                            glVertex3f(x, y, f({x / scale + n / 2, y / scale + m / 2}) * scalez);
                            glVertex3f(x, y + scalex, f({(x) / scale + n / 2, (y + scalex) / scale + m / 2}) * scalez);
                            glVertex3f(x + scalex, y + scalex, f({(x + scalex) / scale + n / 2, (y + scalex) / scale + m / 2}) * scalez);

                            glVertex3f(x, y, f({x / scale + n / 2, y / scale + m / 2}) * scalez);
                            glVertex3f(x + scalex, y, f({(x + scalex) / scale + n / 2, (y) / scale + m / 2}) * scalez);
                            glVertex3f(x + scalex, y + scalex, f({(x + scalex) / scale + n / 2, (y + scalex) / scale + m / 2}) * scalez);
                        } else {
                            glVertex3f(x + scalex, y, f({(x + scalex) / scale + n / 2, (y) / scale + m / 2}) * scalez);
                            glVertex3f(x, y + scalex, f({(x) / scale + n / 2, (y + scalex) / scale + m / 2}) * scalez);
                            glVertex3f(x + scalex, y + scalex, f({(x + scalex) / scale + n / 2, (y + scalex) / scale + m / 2}) * scalez);

                            glVertex3f(x, y, f({x / scale + n / 2, y / scale + m / 2}) * scalez);
                            glVertex3f(x + scalex, y, f({(x + scalex) / scale + n / 2, (y) / scale + m / 2}) * scalez);
                            glVertex3f(x, y + scalex, f({(x) / scale + n / 2, (y + scalex) / scale + m / 2}) * scalez);
                        }
                    }
                }
                    

                glEnd();glBegin(GL_LINES);
                /*if (rand() % (in + im) == 0) {
                glVertex3f(x, y, f({x / scale + n / 2, y / scale + m / 2}) * scalez);
                glVertex3f(x, y, 0);
                }*/
            }
        }
    }glEnd();


    glBegin(GL_LINES);{
        for (int i = 99; i >= 0; --i) {
            pair<ld, ld> ans = ind[i];
            glColor3f(1.0, 0.0, 0.0);
            if (i == 0) {
                //if (lol) cout << ind[i].first << " " << ind[i].second << endl;
                glColor3f(1.0, 1.0, 0.0);
            }
            ld x = (ans.first - n / 2.0) * scale;
            ld y = (ans.second - m / 2.0) * scale;
            /*glVertex3f(x - 7.0, y - 7.0, f(ind[i]) * scalez);
            glVertex3f(x + 7.0, y + 7.0, f(ind[i]) * scalez);
            glVertex3f(x - 7.0, y + 7.0, f(ind[i]) * scalez);
            glVertex3f(x + 7.0, y - 7.0, f(ind[i]) * scalez);*/

            ld d = 3;
            for (double ang = 0; ang <= 360; ang += 20) {
                glVertex3f(x + sin((ang - 20) / 180.0 * 3.14) * d, y + cos((ang - 20) / 180.0 * 3.14) * d, f(ind[i]) * scalez + 5 + (i == 0));
                glVertex3f(x + sin(ang / 180.0 * 3.14) * d, y + cos(ang / 180.0 * 3.14) * d, f(ind[i]) * scalez + 5 + (i == 0));
            }

            //glVertex3f(x, y, 0);
            //glVertex3f(x, y, f(ind[i]) * scalez);
            if (i == 0) {
                cout << ans.first << " " << ans.second << endl;
                d = sqrtl(sqrtl(sqrtl(f(ans)))) * scale;
                glColor3f(1.0, 1.0, 0.0);
                if (flag)
                for (double ang = 0; ang <= 360; ang ++) {
                    if (x + sin((ang - 1) / 180.0 * 3.14) * d < (-n / 2.0) * scale || x + sin((ang - 1) / 180.0 * 3.14) * d > (n / 2.0) * scale
                     || x + sin((ang) / 180.0 * 3.14) * d > (n / 2.0) * scale || x + sin((ang) / 180.0 * 3.14) * d < (-n / 2.0) * scale) continue;
                    if (y + cos((ang - 1) / 180.0 * 3.14) * d < (-m / 2.0) * scale || y + cos((ang - 1) / 180.0 * 3.14) * d > (m / 2.0) * scale
                     || y + cos((ang) / 180.0 * 3.14) * d > (m / 2.0) * scale || y + cos((ang) / 180.0 * 3.14) * d < (-m / 2.0) * scale) continue;
                    glVertex3f(x + sin((ang - 1) / 180.0 * 3.14) * d, y + cos((ang - 1) / 180.0 * 3.14) * d,
                        f({(x + sin((ang - 1) / 180.0 * 3.14) * d) / scale + n / 2.0, (y + cos((ang - 1) / 180.0 * 3.14) * d) / scale + m / 2.0}) * scalez + 5);
                    glVertex3f(x + sin(ang / 180.0 * 3.14) * d, y + cos(ang / 180.0 * 3.14) * d,
                        f({(x + sin(ang / 180.0 * 3.14) * d) / scale + n / 2.0, (y + cos(ang / 180.0 * 3.14) * d) / scale + m / 2.0}) * scalez + 5);
                }
            }
        }
    }glEnd();

    glColor3f(0.5, 0.5, 0.5);
    /*glBegin(GL_LINES);{
        ld x = n / 2.0 * scale;
        ld y = m / 2.0 * scale;
        glVertex2f(-x, -y);
        glVertex2f( x, -y);
        glVertex2f( x, -y);
        glVertex2f( x,  y);
        glVertex2f( x,  y);
        glVertex2f(-x,  y);
        glVertex2f(-x,  y);
        glVertex2f(-x, -y);
    }glEnd();*/

    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);{
        for (int i = 0; i < k; ++i) {
            ld x = (people[i].first - n / 2.0) * scale;
            ld y = (people[i].second - m / 2.0) * scale;
            glVertex3f(x - 3.0, y - 3.0, 5);
            glVertex3f(x + 3.0, y + 3.0, 5);
            glVertex3f(x + 3.0, y - 3.0, 5);
            glVertex3f(x - 3.0, y + 3.0, 5);
        }
    }glEnd();

    ////glPopMatrix();
    glFlush();
    glutSwapBuffers();
}

void Timer(int value) {
    Draw();
    glutTimerFunc(50, Timer, 1);
}

void Initialize() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-800.0, 800.0, -600.0, 600.0, -2000.0, 2000.0);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
}

int gcd (int a, int b) {
    if (b == 0)
        return a;
    else
        return gcd (b, a % b);
}

int main(int argc, char** argv) {
    //freopen("stress", "r", stdin);
    srand(time(NULL));
    cin >> in >> im;
    n = in;
    m = im;
    cin >> k;
    for (int i = 0; i < k; ++i) {
        ld x, y;
        cin >> x >> y;
        people.push_back({x, y});
    }
    cout << "poligones : ";
    cin >> poligones;
    cout << "circle : ";
    cin >> flag;
    cout << "precision : ";
    int prec;
    cin >> prec;
    scale = min(1000.0 / n, 600.0 / m);
    if (prec == 0) prec = 1;
    scalex = scale / ld(prec);
    for (int i = 0; i < population; ++i) ind[i] = {rx(), ry()};
    ans = ind[0];

    mx = 0.001;
    for (ld x = (-n / 2.0) * scale; x <= (n / 2.0) * scale; x += scalex) {
        for (ld y = (-m / 2.0) * scale; y <= (m / 2.0) * scale; y += scalex) {
            mx = max(mx, f({x / scale + n / 2, y / scale + m / 2}));
        }
    }
    scalez = 400.0 / mx;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1800, 1200);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("people");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(Draw);
    glutTimerFunc(50, Timer, 0);
    Initialize();
    glutMainLoop();
    return 0;
}
/*
80 40
5
80 40
80 0
0 40
0 0
40 20



70 60
5
10 10
20 40
40 20
60 0
70 50
*/