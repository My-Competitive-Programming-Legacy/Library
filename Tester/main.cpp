#include <bits/stdc++.h>
/*
Created on 7/25/2021 by Hamza Hassan:
*/
#define space " "
typedef long long int ll;
using namespace std;

// tested on https://cses.fi/problemset/task/1649
/*
 Lazy[v] holds the value that should have been assigned to the index v for example:
 v = 1 , tl = 0 , tr = n-1 , new_val = 10 ---> lazy[1] will contain 10 not (n * 10 )
 */
template<class type>
class LazySegmentTree {
    const int DEFAULT_RETURN_VALUE = 0; // the value which be returned at invalid 'sum' call
    const int DEFAULT_INIT_VALUE = 0;
public:
    int n;
    vector<type> seg;
    vector<type> lazy;

    type combine(type left, type right) {
        return left + right;
    }

    void push(int tl, int tr, int v) {
        if(tl != tr ){
            int tm = (tl + tr)/2 ;
            range_lazy_value(lazy[v], tl , tm , v*2) ;
            range_lazy_value(lazy[v] , tm+1 , tr , 2 * v + 1 ) ;
        }
        lazy[v] = 0;
    }

    // tl may equal to tr
    void range_lazy_value(int new_val, int tl, int tr, int v) {
        seg[v] += new_val * (tr - tl + 1); // edit this if the new_val is delta .
        if (tl != tr)
            lazy[v] += new_val;
    }

    LazySegmentTree(int _n) {
        n = _n;
        seg.resize(4 * n, DEFAULT_INIT_VALUE);
        lazy.resize(4 * n, 0);
    }

    LazySegmentTree(vector<type> &a) : LazySegmentTree((int) a.size()) {
        build(0, n - 1, 1, a);
    }

    type query(int L, int R) {
        return query(L, R, 0, n - 1, 1);
    }

    void point_update(int idx, int new_val) {
        return range_update(idx, idx, new_val, 0, n - 1, 1);
    }

    void range_update(int L, int R, int new_val) {
        return range_update(L, R, new_val, 0, n - 1, 1);
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
            return DEFAULT_RETURN_VALUE; // 0 at range sum
        }
        push(tl, tr, v);
        if (L == tl && R == tr) {
            return seg[v];
        }
        int tm = (tl + tr) / 2;
        type left_sum = query(L, min(R, tm), tl, tm, 2 * v);
        type right_sum = query(max(tm + 1, L), R, tm + 1, tr, 2 * v + 1);
        return combine(left_sum, right_sum);
    }

    void range_update(int L, int R, int new_val, int tl, int tr, int v) {
        if (L > R) {
            return;
        }
        if (L == tl && R == tr) {
            range_lazy_value(new_val, tl, tr, v);
            return ;
        }
        push(tl, tr, v);
        int tm = (tl + tr) / 2;
        range_update(L, min(R, tm), new_val, tl, tm, 2 * v);
        range_update(max(L, tm + 1), R, new_val, tm + 1, tr, 2 * v + 1);
        seg[v] = combine(seg[2 * v], seg[2 * v + 1]);
    }
};


void solve() {
    int n, q;
    cin >> n >> q;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    LazySegmentTree<long long int> seg(a);
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int L, R, delta;
            cin >> L >> R >> delta;
            L -= 1;
            R -= 1;
            seg.range_update(L, R, delta);
        } else {
            int k;
            cin >> k;
            cout << seg.query(k - 1, k - 1) << endl;
        }
    }
    int x =3;
}

const int query = 0;

int main() {
#ifdef  _SHIT
    freopen("../in", "r", stdin);
    freopen("../out", "w", stdout);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int qq = 1;
    if (query == 1)
        cin >> qq;
    for (int i = 1; i <= qq; i++) {
        solve();
    }
}
