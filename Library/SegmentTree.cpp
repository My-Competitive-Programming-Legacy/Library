template<class type>
class SegmentTree {
    const int DEFAULT_RETURN_VALUE =; // the value which be returned at invalid 'sum' call
    const int DEFAULT_INIT_VALUE = ;
public:
    int n;
    vector<type> seg;

    type combine(type left, type right) {
        return min(left, right);
    }

    SegmentTree(int _n) {
        n = _n;
        seg.resize(4 * n, DEFAULT_INIT_VALUE);
    }

    SegmentTree(vector<type> &a) : SegmentTree((int)a.size()) {
        build(0, n - 1, 1, a);
    }

    type query(int L, int R) {
        return query(L, R, 0, n - 1, 1);
    }

    void point_update(int idx, int new_val) {
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