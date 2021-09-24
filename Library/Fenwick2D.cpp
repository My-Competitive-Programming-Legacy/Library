template<class type>
class Fenwick2D {
    // zero based fenwick tree
    int n, m;
    vector<vector<type>> fen;
    bool initialized; // to make sure the methods are used after calling init .

public:
    Fenwick2D() {
        initialized = false;
    }

    void init(int nn, int mm) {
        initialized = true;
        this->n = nn;
        this->m = mm;
        fen.resize(n, vector<type>(m));
    }

    type query(int x, int y) {
        type ans = 0;
        int y1;
        while (x >= 0) {
            y1 = y;
            while (y1 >= 0) {
                ans += fen[x][y1];
                y1 = (y1 & (y1 + 1)) - 1;
            }
            x = (x & (x + 1)) - 1;
        }
        return ans;
    }

    type range_query(int x1, int y1, int x2, int y2) {
        assert(initialized);
        type ans = 0;
        ans = query(x2, y2);
        if (x1 > 0 && y1 > 0) {
            ans += query(x1 - 1, y1 - 1);
        }
        if (y1) {
            ans -= query(x2, y1 - 1);
        }
        if (x1) {
            ans -= query(x1 - 1, y2);
        }
        return ans;
    }

    void update(int x, int y, type delta) {
        assert(initialized);
        assert(x >= 0);
        assert(x < n);
        assert(y < m);
        assert(y >= 0);
        int y1;
        while (x < n) {
            y1 = y;
            while (y1 < m) {
                fen[x][y1] += delta;
                y1 = y1 | (y1 + 1);
            }
            x = x | (x + 1);
        }
    }
};
