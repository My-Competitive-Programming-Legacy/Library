#include <bits/stdc++.h>

using namespace std;
using ll = long long int;

class FloydWarshal {
public:
    /**
     * Tested with https://cses.fi/problemset/result/816948/
     -Note that g is adj matrix
     -Note that the algorithm changes the graph
     -The following properties should be satisfied:
        - g[i][i] = 0 if i == j
        - g[i][j] = LONG_LONG_MAX if i and j aen't connected
     g[i][j] = INF if i and j aren't connected should be satisfied
    **/
    void construct(vector<vector<ll>> &g) {
        int n = (int) g.size();
        const ll INF = LONG_LONG_MAX;
        vector<vector<ll>> ans(n, vector<ll>(n, INF));
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
//                    cout << i << ' ' << j << ' ' << k << endl;
                    if ((g[i][k] != INF) && (g[k][j] != INF))
                        g[i][j] = min(g[i][k] + g[k][j], g[i][j]);
                }
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (g[i][j] == INF) g[i][j] = -1;
            }
        }
    }
};