#include <bits/stdc++.h>

using namespace std;
const int mxN = 200 * 1000 + 4;
const int lgN = 21;
vector<int> g[mxN];
int up[mxN][21];
int tin[mxN], tout[mxN];
int counter = 0;

void dfs(int cur, int par = -1) {
    up[cur][0] = par;
    tin[cur] = counter++;
    for (int i = 1; i < lgN; i++) {
        if (up[cur][i - 1] != -1) {
            up[cur][i] = up[up[cur][i - 1]][i - 1];
        } else {
            up[cur][i] = -1;
        }
    }
    for (auto to: g[cur]) {
        if (to != par) dfs(to, cur);
    }
    tout[cur] = counter++;
}

int is_ancestor(int par, int child) {
    return tin[par] <= tin[child] && tout[child] <= tout[par];
}

int lca(int u, int v) {
    if (is_ancestor(v, u)) {
        return v;
    }
    for (int i = lgN - 1; i >= 0; i--) {
        if (up[v][i] != -1 && !is_ancestor(up[v][i], u)) {
            v = up[v][i];
        }
    }
    return up[v][0];
}

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> val(n);
    for (int i = 0; i < n; i++) {
        cin >> val[i];
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u -= 1;
        v -= 1;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(0, -1);

    while (q--) {
        int u, v;
        cin >> u >> v;
        u -= 1;
        v -= 1;
        int l = lca(u, v);
        int ans = max(val[u], val[v]);
        while (u != l) {
            ans = max(ans, val[u]);
            u = up[u][0];
        }

    }

    return 0;
}