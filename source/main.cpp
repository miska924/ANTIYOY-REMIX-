#include <bits/stdc++.h>

using namespace std;

#include "globals.h"
#include "glutWindow.h"
#include "generate.h"

int main(int argc, char** argv) {
    // srand(time(NULL));
    srand(741423);

    cout << "field & players" << endl;
    cin >> FSZ >> PLAYERS;

    GenerateField();

    GlutWindow(argc, argv);

    return 0;
}