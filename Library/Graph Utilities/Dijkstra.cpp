#include <bits/stdc++.h>

using namespace std;
using ll = long long int;

class Dijkstra {
public:
    // Tested with https://cses.fi/problemset/task/1671/
    vector<ll> get_shortest_paths(vector<vector<pair<ll, int>>> &g, int source) {
        ll INF = LONG_LONG_MAX;
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
        int n = (int) g.size();
        vector<ll> d(n, INF);
        assert(source >= 0 && source < n);
        d[source] = 0;
        pq.push({0, source});
        while (!pq.empty()) {
            ll expected_cost = pq.top().first;
            int u = pq.top().second;
            pq.pop();
            if (d[u] != expected_cost) {
                assert(d[u] < expected_cost);
                continue;
            }
            for (auto adj : g[u]) {
                int to = adj.second;
                ll cost = adj.first;

                if (d[u] + cost < d[to]) {
                    d[to] = d[u] + cost;
                    pq.push({d[to], to});
                }
            }
        }
        for (auto &v : d)
            if (v == INF)
                v = -1;

        return d;
    }
};