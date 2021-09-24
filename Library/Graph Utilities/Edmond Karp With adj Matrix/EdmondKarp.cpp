#include <bits/stdc++.h>
// Tested with https://cses.fi/problemset/task/1694
using namespace std;
using ll = long long int;

const ll INF = LONG_LONG_MAX;
ll bfs(vector<vector<ll>> &g, int s, int t, vector<int> &par) {
    int n = (int) g.size();

    queue<pair<int, ll>> q;
    q.push({s, INF});

    fill(par.begin(), par.end(), -1);
    par[s] = s;

    bool found = false;
    ll ans_flow = 0;

    while (!q.empty() && (!found)) {
        int cur = q.front().first;
        ll flow_so_far = q.front().second;
        q.pop();
        for (int to = 0; to < n; to++) {
            if ((par[to] == -1) && (g[cur][to] > 0)) {
                par[to] = cur;
                q.push({to, min(flow_so_far, g[cur][to])});
                if (to == t) {
                    found = true;
                    ans_flow = min(flow_so_far, g[cur][to]);
                    break;
                }
            }
        }
    }
    if (found) {
        return ans_flow;
    } else {
        return 0;
    }
}

// O(V * E * E )
ll max_flow(vector<vector<ll>> &adj_matrix, int s, int t) {
    int n = (int) adj_matrix.size();

    ll flow = 0;
    vector<int> par(n);
    ll new_flow = bfs(adj_matrix, s, t, par);
    while (new_flow > 0) {
        flow += new_flow;

        int cur = t;
        while (cur != s) {
            int prev = par[cur];
            adj_matrix[prev][cur] -= new_flow;
            adj_matrix[cur][prev] += new_flow;
            cur = prev;
        }

        new_flow = bfs(adj_matrix, s, t, par);
    }
    return flow;
}

int main() {
#ifdef  _SHIT
    freopen("../in" , "r" , stdin) ;
    freopen("../out" , "w" , stdout) ;
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n,m;
    cin >> n>> m ;
    vector<vector<ll>> g(n,vector<ll>(n)) ;
    for(int i=0;i<m;i++){
        int u ,v , c ;
        cin >> u >> v >> c ;
        u--;v-- ;
        g[u][v] += c ;

    }
    cout << max_flow(g, 0 , n-1) << endl;
    return 0;
}