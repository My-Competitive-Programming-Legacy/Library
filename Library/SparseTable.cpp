template<class type>
class SparseTable {
private:
    int n;
    const int INIT_VALUE = ; // EDIT HERE
    vector<vector<type>> table;
    // always edit this function
    type combine(type a, type b) {
        return min(a, b);
    }
    // DON'T FUCK WITH THIS CODE
public:
    SparseTable(vector<type> &a) {
        n = (int) a.size();
        int lg = (int)log2((n));
        table.resize(n, vector<type>(lg + 1, INIT_VALUE));
        for (int i = 0; i < n; i++) {
            table[i][0] = a[i];
        }
        for (int bit = 1; bit <= lg; bit++) {
            for (int i = 0; i + (1 << (bit - 1)) < n; i++) {

                table[i][bit] = combine(table[i][bit - 1], table[i + (1 << (bit - 1))][bit - 1]);

            }
        }
    }

    type get(int L, int R) {
        assert(L >= 0 && L < n);
        assert(R >= 0 && R < n && R >= L);
        int len = (int) (log2((R - L + 1)));
        return combine(table[L][len], table[R - (1<<len) + 1 ][len]);
    }

};