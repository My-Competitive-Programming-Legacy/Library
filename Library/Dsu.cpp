struct Dsu {
    vector<int> dsu;
    vector<int> size;
    int n;

    Dsu(int n) {
        this->n = n;
        dsu.resize(n);
        size.resize(n);
    }

    void init() {
        for (int i = 0; i < n; i++) {
            dsu[i] = i;
            size[i] = 1;

        }
    }

    int get_parent(int u) {
        if (dsu[u] == u) return u;
            // path compression
        else
            return dsu[u] = get_parent(dsu[u]);
    }

    bool merge(int u, int v) {
        int pu = get_parent(u);
        int pv = get_parent(v);

        if (pu == pv)
            return false;

        if (size[pu] > size[pv]) {
            swap(pu, pv);
        }
        // the one with larger size is the parent
        // pu -> the smaller size
        dsu[pu] = pv;
        size[pv] += size[pu];


        return true;
    }


    int count_components() {
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (dsu[i] == i) {
                ans += 1;
            }
        }
        return ans;
    }
};