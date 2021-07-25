/*
 Lazy[v] holds the value that should have been assigned to the index v for example:
 v = 1 , tl = 0 , tr = n-1 , new_val = 10 ---> lazy[1] will contain 10 not (n * 10 )
 However, we store lazy[v] so that we can delegate it to the children but seg[v] is always correct(v whose lazy[v] is not zero)
 */
template<class type>
class LazySegmentTree {
    const type DEFAULT_RETURN_VALUE = 0; // the value which be returned at invalid 'sum' call
    const type DEFAULT_INIT_VALUE = 0;
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
    void range_lazy_value(type new_val, int tl, int tr, int v) {
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