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
    int n = rng()%10 + 1 ;
    int q=  rng()%4 + 1  ;

    cout << n << ' ' << q <<endl;
    for(int i=0;i<n;i++){
        cout << rng()%V + 1 << ' ';
    }
    cout << endl;
    while(q--){
        int type = rng()%2+1;
        if(type == 1 ) {
            int R = rng()%n + 1 ;
            int L = rng()%R + 1 ;
            int delta = rng()%V + 1 ;
            cout <<1 << ' ' << L << ' ' << R << ' ' << delta << endl;
        }else {
            int idx = rng()%n + 1 ;
            cout << 2 << ' ' << idx <<endl;
        }
    }

}