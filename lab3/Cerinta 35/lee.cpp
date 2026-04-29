#include "lee.h"

#include "../TAD Coada/Proiect C++/Coada.h"

#include <climits>
#include <stdexcept>
#include <utility>
#include <vector>

namespace A {
    bool Lee::inside(int i, int j) { return i >= 0 and j >= 0 and i < n and j < m; }

    int Lee::codify(int i, int j) { return i * m + j; }

    pair<int, int> Lee::decodify(int i) { return {i / n, i % n}; }

    pair<int, int> Lee::find_min_position() {
        int mn_path = INT_MAX / 2;
        pair<int, int> ans = {-1, -1};
        for (int i = 1; i < n - 1; i++) {
            if (dist[i][0] != INT_MAX / 2) {
                if (ans.first == -1)
                    ans = {i, 0}, mn_path = dist[i][0];
                else if (dist[i][0] < mn_path)
                    mn_path = dist[i][0], ans = {i, 0};
            }
            if (dist[i][m - 1] != INT_MAX / 2) {
                if (ans.first == -1)
                    ans = {i, m - 1}, mn_path = dist[i][m - 1];
                else if (dist[i][m - 1] < mn_path)
                    mn_path = dist[i][m - 1], ans = {i, m - 1};
            }
        }

        for (int j = 0; j < m; j++)
            if (dist[0][j] != INT_MAX / 2) {
                if (ans.first == -1)
                    ans = {0, j}, mn_path = dist[0][j];
                else if (dist[0][j] < mn_path)
                    mn_path = dist[0][j], ans = {0, j};
            }

        for (int j = 0; j < m; j++)
            if (dist[n - 1][j] != INT_MAX / 2) {
                if (ans.first == -1)
                    ans = {n - 1, j}, mn_path = dist[n - 1][j];
                else if (dist[n - 1][j] < mn_path)
                    mn_path = dist[n - 1][j], ans = {n - 1, j};
            }

        return ans;
    }

    Lee::Lee(int nrlinii, int nrcol) {
        this->n = nrlinii;
        this->m = nrcol;
        road = new int *[n];
        dist = new int *[n];
        for (int i = 0; i < n; i++) {
            road[i] = new int[m];
            dist[i] = new int[m];

            for (int j = 0; j < m; j++) {
                road[i][j] = -1;
                dist[i][j] = INT_MAX / 2;
            }
        }
    }

    void Lee::lee_propag(int isrc, int jsrc, bool **mat) {
        if (isrc == -1)
            throw runtime_error("Punctul de start nu exista");

        if (!inside(isrc, jsrc))
            throw runtime_error(
                "Punctul de start nu se afla in interiorul matricei");

        Coada que;
        que.adauga(codify(isrc, jsrc));
        road[isrc][jsrc] = -1;
        dist[isrc][jsrc] = 0;

        while (!que.vida()) {
            int code = que.sterge();
            auto [i, j] = decodify(code);

            for (int d = 0; d < 4; d++) {
                int ii = di[d] + i;
                int jj = dj[d] + j;

                if (inside(ii, jj) and dist[ii][jj] > dist[i][j] + 1 and
                    mat[ii][jj] == 0) {
                    dist[ii][jj] = dist[i][j] + 1;
                    road[ii][jj] = d;
                    que.adauga(codify(ii, jj));
                }
            }
        }
    }

    int Lee::min_path_distance() {
        auto [i, j] = find_min_position();
        if (i == -1) {
            throw runtime_error("Nu avem un punct pe unde sa ies");
        }

        return dist[i][j];
    }

    void Lee::marsul_piticilor(int i, int j) {
        if (road[i][j] == -1) {
            min_path_road.emplace_back(i, j);
            return;
        }
        int d = road[i][j];
        int ii = -di[d] + i;
        int jj = -dj[d] + j;

        marsul_piticilor(ii, jj);
        min_path_road.emplace_back(i, j);
    }

    std::vector<std::pair<int, int>> Lee::path() {
        auto [i, j] = find_min_position();

        marsul_piticilor(i,j);
        return min_path_road;
    }
} // namespace A

