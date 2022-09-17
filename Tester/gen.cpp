#include <bits/stdc++.h>
#include <chrono>

#include <iostream>
#include <random>

#define space " "
#define vi vector<int>
using namespace std;
mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
long long int N = 8;
long long int Q = 100;
long long int V = 6;
#define ll long long int

int main() {
    int n = 100000 + 1;
    int m = 100000 + 1 + n - 1;
    cout << n << ' ' << m << endl;
    set<pair<int, int>> st;
    for (int i = 1; i < n; i++) {
        cout << i - 1 << ' ' << i << ' ' << 1 << endl;
        st.insert({i - 1, i});
    }
    for (int i = 0; i < m; i++) {
        int u = rng() % n + 1;
        int v = rng() % n + 1;
//        while (st.count({u, v})) {
//            int u = rng() % n + 1;
//            int v = rng() % m + 1;
//        }
        st.insert({u,v});
        cout << u << ' ' << v << ' ' << 1 << endl;
    }
    cout << endl;

}