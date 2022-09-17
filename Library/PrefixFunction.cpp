#include<bits/stdc++.h>

using namespace std;
struct PrefixFunction{
    string s;
    vector<int> pi;
    PrefixFunction(string s):s(s){
        int n =(int)s.size();
        pi.resize(n,0);
        for(int i=1;i<n;i++){
            int j = pi[i-1];
            while(j >0 && s[i] != s[j]){
                j = pi[j-1];
            }
            if(s[i] == s[j]){
                j++;
            }
            pi[i] = j;
        }
    }


};
int main() {
    // https://cses.fi/problemset/task/1753
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string s, text;
    cin >> text >> s;
    int n = (int)s.size();
    s.push_back('#');
    string new_s = s + text;
    PrefixFunction p(new_s);
    vector<int> &lp = p.pi;
    int answer=0;
    for(int i=0;i<(int)lp.size();i++){
        if(lp[i] == n){
            answer +=1;
        }
    }
    cout <<answer << endl;
    return 0;
}
