//https://cses.fi/problemset/task/1696
#include <bits/stdc++.h>

using namespace std;


using ll = long long int;
const ll INF = LONG_LONG_MAX;


// O(V * E * E )
struct Edge {
    int u, v;
    ll cost;

    Edge(int u, int v, ll cost) : u(u), v(v), cost(cost) {

    }

    Edge() {
        u = 0, v = 0, cost = 0;
    }
};

class Edmond {
public:
    vector<Edge> edges;
    vector<vector<int>> adj;
    int n;

    Edmond(vector<Edge> &edges, vector<vector<int>> &adj) : edges(edges), adj(adj) {
        n = (int) adj.size();
    }

    const ll INF = LONG_LONG_MAX;

    ll bfs(int s, int t, vector<int> &par) {
        fill(par.begin(), par.end(), -1);
        par[s] = s;
        queue<pair<int, ll>> q;
        q.push({s, INF});
        ll ans_flow = 0;
        while ((!ans_flow) && (!q.empty())) {
            int cur = q.front().first;
            ll flow_so_far = q.front().second;
            q.pop();
            for (auto e_to: adj[cur]) {
                int to = edges[e_to].v;
                ll cost = edges[e_to].cost;
                if (par[to] == -1 && (cost > 0)) {
                    q.push({to, min(flow_so_far, cost)});
                    par[to] = e_to; // save the index of the edge to be able to edit later
                    if (to == t) {
                        ans_flow = min(flow_so_far, cost);
                        break;
                    }
                }
            }
        }
        if (!ans_flow) {
            return 0LL;
        } else {
            return ans_flow;
        }
    }

    ll max_flow(int s, int t) {
        ll flow = 0;
        vector<int> par(n);
        ll cur_flow = bfs(s, t, par);
        while (cur_flow != 0) {
            flow += cur_flow;
            int cur = t;
            while (cur != s) {
                int e_idx = par[cur];
                assert(edges[e_idx].v == cur);
                int prev = edges[e_idx].u;
                edges[e_idx].cost -= cur_flow;
                if (e_idx % 2 == 0) {
                    // this means it is original edge
                    edges[e_idx + 1].cost += cur_flow;
                } else {
                    edges[e_idx - 1].cost += cur_flow;
                }
                cur = prev;
            }
            cur_flow = bfs(s, t, par);
        }
        return flow;
    }

    vector<pair<int, int>> min_cuts(int s, int t) {
        ll flow = max_flow(s, t);
        set<int> st; // set of reachable states in resedual graph
        function<void(int)> Dfs = [&](int cur) {
            st.insert(cur);
            for (auto e : adj[cur]) {
                int u = edges[e].u;
                int v = edges[e].v;
                ll cost = edges[e].cost;
                assert(cur == u);
                if (!st.count(v) && cost > 0) {
                    Dfs(v);
                }
            }
        };
        Dfs(s);
        vector<pair<int, int>> ans;
        for (int i = 0; i < (int) edges.size(); i++) {
            // Note that we usually loop over original edges so if your graph is one directed,
            // you may increment the i coutner by 2 in each step
            int u = edges[i].u;
            int v = edges[i].v;
            if (st.count(u) && !st.count(v)) {
                ans.push_back({u, v});
            }
        }
        assert(ans.size() == flow);
        return ans;
    }

    vector<pair<int, int>> unweighted_matching(int s, int t, int nL, int nR) {
        ll flow = max_flow(s, t);
        vector<pair<int, int>> ans;
        for (auto e : edges) {
            if (e.u >= 1 && e.u <= nL && e.v >= nL && e.v <= nL + nR && e.cost == 0) {
                ans.push_back({e.u, e.v});
            }
        }
        assert(ans.size() == flow);
        return ans;
    }
};

int main() {
#ifdef  _SHIT
    freopen("../in", "r", stdin);
    freopen("../out", "w", stdout);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> adj(n + m + 2);
    vector<Edge> edges(2 * k);
    int start = 0;
    int end = n + m + 1;
    for (int i = 0; i < k; i++) {
        int u, v;
        cin >> u >> v;
        v += n;
        edges[i * 2] = {u, v, 1};
        edges[2 * i + 1] = {v, u, 0}; // reverse edge
        adj[u].push_back(2 * i);
        adj[v].push_back(2 * i + 1);

    }
    for (int i = 1; i <= n; i++) {
        edges.push_back({start, i, 1});
        adj[start].push_back((int) edges.size() - 1);
        edges.push_back({i, start, 0});
        adj[i].push_back((int) edges.size() - 1);
    }
    for (int i = 1; i <= m; i++) {
        edges.push_back({n + i, end, 1});
        adj[n + i].push_back((int) edges.size() - 1);

        edges.push_back({end, n + i, 0});

        adj[end].push_back((int) edges.size() - 1);

    }
    Edmond flow(edges, adj);
    vector<pair<int, int>> ans = flow.unweighted_matching(start, end, n, m);
    cout << ans.size() << endl;
    for (auto p : ans) {
        cout << p.first << ' ' << p.second - n<< endl;
    }

    return 0;
}