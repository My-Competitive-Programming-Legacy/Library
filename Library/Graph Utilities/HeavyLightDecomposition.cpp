#include <bits/stdc++.h>

using namespace std;

class HeavyLightDecompositionUtil {
public:
    vector<int> parent, heavy, head, depth, id;
    int timer;

    void init(vector<vector<int>> &g) {
        int n = (int) g.size();
        parent.resize(n); // parent[root] = root
        heavy.resize(n, -1);
        head.resize(n);
        depth.resize(n, 0);
        id.resize(n);

        int root = 0;
        dfs(root, 0, g);
        timer = 0;
        decompose(root, root, 0, g);
        // please notice that head[i] = i if i is the root (not -1)
    }

    int dfs(int cur, int par, vector<vector<int>> &g) {
        parent[cur] = par;
        depth[cur] = 1 + depth[par];
        int size =1;
        int max_subtree_size = 0;
        for (auto to: g[cur]) {
            if (to != par) {
                int his_size = dfs(to, cur, g);
                size += his_size;
                if (his_size > max_subtree_size) {
                    max_subtree_size = his_size;
                    heavy[cur] = to;
                }
            }
        }
        return size; // count myself
    }

    void decompose(int cur, int h, int par, vector<vector<int>> &g) {
        head[cur] = h, id[cur] = timer++;
        if (heavy[cur] != -1) {
            decompose(heavy[cur], h, cur, g);
        }
        for (auto to: g[cur]) {
            if (to != par && to != heavy[cur]) {
                decompose(to, to, cur, g);
            }
        }
    }

    int lca(int u, int v) {
        while (head[u] != head[v]) {
            if (depth[head[u]] < depth[head[v]]) {
                swap(u, v); // make u deeper
            }
            u = parent[head[u]];
        }
        if (depth[u] < depth[v]) {
            swap(u, v);
        }
        return v;
    }
};
