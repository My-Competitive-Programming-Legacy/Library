struct TrieNode {
    int end;
    TrieNode *nxt[2];

    TrieNode() {
        end = 0;
        nxt[0] = nullptr;
        nxt[1] = nullptr;
    }
};
int mxb = 30;
void insert(TrieNode *root, int val, int bidx = mxb) {
    if (bidx == -1) {
        root->end += 1;
        return;
    }
    int bit = (val & (1 << bidx)) != 0;
    if (root->nxt[bit] == nullptr) {
        root->nxt[bit] = new TrieNode();
    }
    insert(root->nxt[bit], val, bidx - 1);

}
TrieNode *delete_one(TrieNode *root, int val, int bidx = mxb) {
    if (bidx == -1) {
        assert(root->end > 0);
        root->end -= 1;
        if (root->end > 0)
            return root;
        else if (root->nxt[0] != nullptr && root->nxt[1] != nullptr) {
            return root;
        } else {
            return nullptr;
        }
    }
    int bit = (val & (1 << bidx)) != 0;
    assert(root->nxt[bit] != nullptr);
    root->nxt[bit] = delete_one(root->nxt[bit], val, bidx - 1);
    if (root->nxt[0] == nullptr && root->nxt[1] == nullptr && root->end == 0) {
        return nullptr;
    }
    return root;
}
int get_max(TrieNode *root, int x) {
    int ans = 0;
    for (int i = mxb; i >= 0; i--) {
        int bit = ((1 << i) & x) != 0;
        bit ^= 1;
        if (root->nxt[bit] != nullptr) {
            ans |= (1 << i);
            root = root->nxt[bit];
        } else if (root->nxt[1 ^ bit] != nullptr) {
            root = root->nxt[1 ^ bit];
        } else {
            cerr << x << endl;
            assert(false);
        }

    }
    return ans;
}

void dfs(TrieNode *root, int bidx = mxb, int ans = 0) {
    if (bidx == -1) {
        cout << "Reached " << ans << endl;
        return;
    }

    if (root->nxt[0] != nullptr) {
        dfs(root->nxt[0], bidx - 1, ans);
    }
    if (root->nxt[1] != nullptr) {
        dfs(root->nxt[1], bidx - 1, (1 << bidx) | ans);
    }

}
