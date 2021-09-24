struct Graph {
    vii g;
    int n;
    vi low, in, vis, lvl;
    int timer = 1;
    int bridges = 0;

    Graph(int n) {
        this->n = n;
        g.resize(n);
        for (int i = 0; i < n; i++) {
            low.pb(INF);
            in.pb(0);
            vis.pb(0);
            lvl.pb(0);
        }
    }

    void add_edge(int u, int v) {
        g[u].pb(v);
    }

    void dfs(int cur, int par = -1, int level = 0) {
        //cerr << "going from par = " << par + 1 << "to cur = " << cur + 1 << endl;
        vis[cur] = 1;
        lvl[cur] = level;
        in[cur] = timer++;
        for (auto to  : g[cur]) {
            if (!vis[to]) {
                dfs(to, cur, level + 1);
            }
        }
        for (auto to : g[cur]) {
            if (to == par) continue;
            low[cur] = min(low[to], low[cur]);
            low[cur] = min(in[to], low[cur]);
        }
        if (par != -1) {
            if (low[cur] > in[par]) bridges++;

        }
    }

    void print_res() {
        for (int i = 0; i < n; i++) {
            for (auto to : g[i]) {
                if (in[to] > in[i]) {
                    if (lvl[to] - lvl[i] == 1) cout << i + 1 << space << to + 1 << endl;
                    else cout << to + 1 << space << i + 1 << endl;
                }
            }
        }
    }
};