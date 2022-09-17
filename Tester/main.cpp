#include <bits/stdc++.h>

using namespace std;

template<class type>
class SegmentTree {
    const int DEFAULT_RETURN_VALUE = INT_MIN; // the value which be returned at invalid 'sum' call
    const int DEFAULT_INIT_VALUE = INT_MIN;
public:
    int n;
    vector<type> seg;

    type combine(type left, type right) {
        return max(left, right);
    }

    SegmentTree(int _n) {
        n = _n;
        seg.resize(4 * n, DEFAULT_INIT_VALUE);
    }

    SegmentTree(vector<type> &a) : SegmentTree((int) a.size()) {
        build(0, n - 1, 1, a);
    }

    type query(int L, int R) {
        return query(L, R, 0, n - 1, 1);
    }

    void point_update(int idx, int new_val) {
        assert(idx < n);
        return point_update(idx, new_val, 0, n - 1, 1);
    }

private:
    void build(int tl, int tr, int v, vector<type> &a) {
        if (tl == tr) {
            seg[v] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(tl, tm, v * 2, a);
            build(tm + 1, tr, v * 2 + 1, a);
            seg[v] = combine(seg[2 * v], seg[2 * v + 1]);
        }
    }

    type query(int L, int R, int tl, int tr, int v) {
        if (L > R) {
            return DEFAULT_RETURN_VALUE; // 0 at ragne sum
        }
        if (L == tl && R == tr) {
            return seg[v];
        }
        int tm = (tl + tr) / 2;
        type left_sum = query(L, min(R, tm), tl, tm, 2 * v);
        type right_sum = query(max(tm + 1, L), R, tm + 1, tr, 2 * v + 1);
        return combine(left_sum, right_sum);
    }

    void point_update(int idx, type new_val, int tl, int tr, int v) {
        if (tl == tr) {
            assert(idx == tl);
            seg[v] = new_val;
            return;
        }
        int tm = (tl + tr) / 2;
        if (idx <= tm) {
            point_update(idx, new_val, tl, tm, v * 2);
        } else {
            point_update(idx, new_val, tm + 1, tr, 2 * v + 1);
        }
        seg[v] = combine(seg[v * 2], seg[v * 2 + 1]);
    }

};

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
        depth[cur] = 1 + depth[par]; // depth of root = 1

        int max_subtree_size = 0;
        for (auto to: g[cur]) {
            if (to != par) {
                int his_size = dfs(to, cur, g);
                if (his_size > max_subtree_size) {
                    max_subtree_size = his_size;
                    heavy[cur] = to;
                }
            }
        }
        return max_subtree_size + 1; // count myself
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

int main() {
#ifdef  _SHIT
    freopen("../in", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif
    int n, q;
    cin >> n >> q;
    vector<int> val(n);
    vector<vector<int>> g(n);
    for (int i = 0; i < n; i++) {
        cin >> val[i];
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    HeavyLightDecompositionUtil hld;
    hld.init(g);
    SegmentTree<int> seg(n);
    for (int i = 0; i < n; i++) {
        seg.point_update(hld.id[i], val[i]);
    }
    vector<int> &head = hld.head;
    vector<int> &heavy = hld.heavy;
    vector<int> &id = hld.id;
    vector<int> &depth = hld.depth;
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int u;
            cin >> u;
            u -= 1;
            int new_value;
            cin >> new_value;
            seg.point_update(hld.id[u], new_value);
        } else {
            int u, v;
            cin >> u >> v;
            u -= 1;
            v -= 1;

            int ans = INT_MIN;
            while (head[u] != head[v]) {
                if (depth[u] < depth[v])
                    swap(u, v); // make the u deepeer

                assert(id[head[u]] <= id[u]);
                ans = max(ans, seg.query(id[head[u]], id[u]));
                u = hld.parent[head[u]];
            }
            if (depth[u] < depth[v])
                swap(u, v);

            assert(head[u] == head[v]);
            ans = max(ans, seg.query(id[v], id[u]));
            cout << ans << ' ';
        }
    }
    cout << endl;
    return 0;
}