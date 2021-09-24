struct Scc {
    vector<vector<int>> g;
    vector<vector<int>> g_rev;
    vector<vector<int>> components;
    vector<int> order; // descending in terms of tout
    vector<int> vis;
    vector<int> id; // id[v] is the number of connected component to which v belong
    int n;

    Scc(vector<vector<int>> &g) : g(g) {
        n = (int) g.size();
        g_rev.resize(n);
        for (int i = 0; i < n; i++) {
            for (auto to : g[i]) {
                g_rev[to].push_back(i);
            }
        }
        vis.resize(n, false);
        id.resize(n);
    }

    void dfs1(int cur) {
        vis[cur] = true;
        for (auto to: g[cur]) {
            if (!vis[to]) {
                dfs1(to);
            }
        }
        order.push_back(cur);
    }

    void dfs2(int cur) {
        vis[cur] = true;
        components.back().push_back(cur);
        id[cur] = components.size() - 1;
        for (auto to : g_rev[cur]) {
            if (!vis[to]) {
                dfs2(to);
            }
        }
    }

    int find_all() {
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                dfs1(i);
            }
        }
        fill(vis.begin(), vis.end(), false);
        int ans = 0;
        reverse(order.begin(), order.end());
        for (auto v : order) {
            if (!vis[v]) {
                ans++;
                components.emplace_back();
                dfs2(v);
            }
        }
        return ans;
    }

    void print() {
        for (auto comp : components) {
            for (auto v : comp) {
                cout << v << ' ';
            }
            cout << endl;
        }
    }
};
