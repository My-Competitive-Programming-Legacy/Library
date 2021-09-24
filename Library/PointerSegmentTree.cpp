#include <bits/stdc++.h>

using namespace std;

// provides more flexibilty, but is 100ms slower that our normal lazySegmentTree
// For more details check my submission of polynomial queries on cses
struct Node {
private:
    long long int val;
    long long int lazy;
public:
    int tl, tr; // seems that if they are long long that will be more safe :D
    long long int DEFAULT_RETURN_VALUE = 0;
    Node *left;
    Node *right;
    Node(int tll, int trr) {
        tl = tll, tr = trr, val = -1, lazy = 0;
        left = nullptr;
        right = nullptr;
    }
    void combine() {
        assert(tl != tr);
        val = left->val + right->val;
    }
    // it is called in the build function when tl = tr otherwise, combine() is called :) 
    void set_value(long long int value) {
        val = value;
    }
    void push_down() {
        if (tl != tr) {
            assert(left != nullptr && right != nullptr);
            left->range_lazy_value(lazy);
            right->range_lazy_value(lazy);
        }
        lazy = 0;
    }
    void range_lazy_value(long long int new_value) {
        val += (tr - tl + 1) * new_value; // CHECKOUT HERE THE INTEGER OVERFLOW (IMPORTANT) 
        lazy += new_value;
    }
    long long int get_value() {
        return val; // not always that simple
    }
    static long long int combine2(long long int first, long long int second) {
        long long int ans = 0;
        ans = first + second;
        return ans;
    }
};

template<class Node, class type>
class SegmentTree {
public:
    Node *root;
    int n;

    SegmentTree(int _n) {
        n = _n;
    }
    SegmentTree(vector<type> &a) : SegmentTree((int) a.size()) {
        root = build(0, n - 1, a);
    }
    type query(int L, int R) {
        return query(L, R, 0, n - 1, root);
    }
    void point_update(int idx, type new_val) {
        return range_update(idx, idx, new_val, 0, n - 1, root);
    }
    void range_update(int L, int R, type new_val) {
        return range_update(L, R, new_val, 0, n - 1, root);
    }

private:
    Node *build(int tl, int tr, vector<type> &a) {
        Node *ret = new Node(tl, tr);
        if (tl == tr) {
            ret->set_value(a[tl]);
        } else {
            int tm = (tl + tr) / 2;
            Node *left = nullptr, *right = nullptr;
            left = build(tl, tm, a);
            right = build(tm + 1, tr, a);
            ret->left = left;
            ret->right = right;
            ret->combine();
        }
        return ret;
    }

    type query(int L, int R, int tl, int tr, Node *v) {
        if (L > R) {
            return v->DEFAULT_RETURN_VALUE; // 0 at range sum
        }
        v->push_down();
        if (L == tl && R == tr) {
            return v->get_value();
        }
        int tm = (tl + tr) / 2;

        type left_sum = query(L, min(R, tm), tl, tm, v->left);
        type right_sum = query(max(tm + 1, L), R, tm + 1, tr, v->right);
        return Node::combine2(left_sum, right_sum);
    }

    void range_update(int L, int R, type new_val, int tl, int tr, Node *v) {
        if (L > R) {
            return;
        }
        if (L == tl && R == tr) {
            v->range_lazy_value(new_val);
            return;
        }
        v->push_down();
        int tm = (tl + tr) / 2;
        range_update(L, min(R, tm), new_val, tl, tm, v->left);
        range_update(max(L, tm + 1), R, new_val, tm + 1, tr, v->right);
        v->combine();
    }
};