#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
#define space " "
#define debug(val) "[ " << #val " : " << (val) << " ]" << space
#define vi vector<int>
#define vl vector<ll>
#define vll vector<vector<ll>>
#define vii vector<vector<int>>
#define PI (double)(atan(1)*4)
#define pb push_back
#define ff first
#define ss second
#define pi pair<int , int >
#define INF LONG_LONG_MAX
#define EPS (double)0.0000000001
#define mp make_pair

// Find pow(a,b) mod (mod) where mod could be any number
int powmod(ll a, ll b, ll mod) {
    ll ans = 1;
    while (b > 0) {
        if (b & 1) {
            ans = (ans * a) % mod;
        }
        b >>= 1;
        a = (a * 1LL * a) % mod;
    }
    return ans;
}

// Find the Bezout's coefficient of a , b --> a X + b Y = gcd(a,b)
int gcdExtended(int a, int b, int *x, int *y) {
    if (a == 0) {
        *x = 0, *y = 1;
        return b;
    }
    int x1, y1;
    int gcd = gcdExtended(b % a, a, &x1, &y1);
    *x = y1 - (b / a) * x1;
    *y = x1;
    return gcd;
}

// Find the modular inverse of a mod m (m can be any number
// but 'a' and 'b' could be coprimes
int modInverse(int a, int m) {
    int x, y;
    int g = gcdExtended(a, m, &x, &y);
    if (g != 1)
        cout << "Fuck , Inverse doesn't exist";
    else {
        // m is added to handle negative x
        int res = (x % m + m) % m;
        return res;
        // cout << "Modular multiplicative inverse is " << res;
    }
    return -1;
}

// Calucate X % mod where X  = AAAAA.... n times
// N<= 10 ^ 12 , stoi(A) <= 10^3  I turned it into string to make life easier
// problem Link : https://www.hackerrank.com/challenges/eugene-and-big-number/problem
int solve(string A, ll n, ll mod) {
    int len = A.size();
    if (n == 1) {
        return stol(A) % mod;
    } else {
        ll sz = n / 2;
        int mid = solve(A, sz, mod);
        int exp = powmod(10, sz * 1LL * len, mod);
        ll ans = mid + (exp * 1LL * mid) % mod;
        ans %= mod;
        if (n % 2 == 1) {
            int exp2 = powmod(10, len, mod);
            ans = (ans * 1LL * exp2) % mod;
            ans += stol(A);
            ans %= mod;
//            ans = (ans * 1LL * 10 * len  + 1) % mod;
        }
        return ans;
    }
}

void solve() {

}

//#define _DEBUG

int main() {
#ifdef _DEBUG
    freopen("in.txt", "r", stdin);
    freopen("out2.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0); // FAST IO
    int q = 1;
//    cin >> q;
    for (int i = 1; i <= q; i++) {
        // cout << "Case #" << i << ": ";
        solve();
    }
}