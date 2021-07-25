#include <bits/stdc++.h>
/*
Created on  by Hamza Hassan:
*/
#define space " "
typedef long long int ll;
#define debug(val) "[ " << #val " : " << (val) << " ]" << space
using namespace std;

int n, q;
ll fen[2 * 100000 + 3];
void build() {
    for (int i = 0; i <= n; i++) fen[i] = 0;
}

ll sum(int r) {
    ll ans = 0;
    for (; r > 0; r -= (r & (-r))) ans += fen[r];
    return ans;
}

ll sum(int l, int r) {
    return sum(r) - sum(l - 1);
}

void update(int idx, int delta) {
    for (; idx <= n; idx += (idx & (-idx))) fen[idx] += delta;
}

void range_update(int l, int r, int delta) {
    update(l, delta);
    if (r < n) update(r + 1, -delta);
}

int main() {
#ifdef _DEBUG // place in cmake-build-debug folder
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    cin >> n >> q;
    vector<int> ar(n + 1);
    build();
    for (int i = 1; i <= n; i++) {
        cin >> ar[i];
        range_update(i, i, ar[i]);
    }
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int a, b, c;
            cin >> a >> b >> c;
            range_update(a, b, c);
        } else {
            int a;
            cin >> a;
            cout << sum(a) << endl;
        }

    }


    return 0;
}

//int n, m, k;
//vector<vector<char>> a;
//const bool query = true;
//bool solve(int i, int j) {
//    int cnt = 0;
//    if (i == n && j == 0) {
//        for (int i = 0; i < n; i++) {
//            for (int j = 0; j < m; j++) {
//                if (a[i][j] == '.') {
//                    return false;
//                } else {
//                    if (a[i][j] == 'H')cnt += 1;
//                }
//            }
//        }
//        if (cnt == k * 2) {
//            int x = 4;
//        }
//        return cnt == k * 2;
//    }
//    int nr = i;
//    int nc = j + 1;
//    if (j + 1 == m) {
//        nr += 1;
//        nc = 0;
//    }
//    if (a[i][j] != '.') {
//        return solve(nr, nc);
//    }
//
//    if (j + 1 < m && a[i][j + 1] == '.') {
//        a[i][j] = 'H';
//        a[i][j + 1] = 'H';
//        if (solve(nr, nc))return true;
//        a[i][j + 1] = '.';
//        a[i][j] = '.';
//    }
//    if (i + 1 < n && a[i + 1][j] == '.') {
//        a[i][j] = 'V';
//        a[i + 1][j] = 'V';
//        if (solve(nr, nc)) return true;
//        a[i + 1][j] = '.';
//        a[i][j] = '.';
//    }
//    return false;
//}
