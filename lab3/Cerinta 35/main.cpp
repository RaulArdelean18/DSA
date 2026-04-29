#include "lee.h"
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

int main() {
    int n, m;

    cout << "Numarul de linii a matricei: ";
    cin >> n;

    cout << "Numarul de coloane a matricei: ";
    cin >> m;
    cout << "Matricea: \n";

    bool **mat = new bool *[n];
    int isrc = -1, jsrc = -1;

    for (int i = 0; i < n; i++) {
        mat[i] = new bool[m];

        for (int j = 0; j < m; j++) {
            char ch;
            cin >> ch;

            if (ch == 'X')
                mat[i][j] = 1;
            else {
                mat[i][j] = 0;
                if (ch == 'R')
                    isrc = i, jsrc = j;
            }
        }
    }
    try {
        A::Lee it(n, m);
        it.lee_propag(isrc, jsrc, mat);
        int mn_path = it.min_path_distance();

        cout << "Cel mai scurt drum are distanta: " << mn_path << '\n';
        cout << "\nDrumul de lungime minima:\n";
        std::vector<std::pair<int, int>> min_path_road = it.path();
        for (auto x : min_path_road)
            cout << x.first << ' ' << x.second << '\n';
    } catch (const exception &exception) {
        cout << "Eroare: " << exception.what() << '\n';
    }
    return 0;
}