// https://marisaoj.com/problem/130
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6 + 5;

int lab[MAXN];

int findset(int u){
    return lab[u] < 0 ? u : lab[u] = findset(lab[u]);
}

void unionset(int a, int b){
    if(lab[a] > lab[b]) swap(a, b);
    lab[a] += lab[b];
    lab[b] = a;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    memset(lab, -1, sizeof(lab));
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= m; i++){
        int t, u, v; cin >> t >> u >> v;
        int a = findset(u),
            b = findset(v);
        if(t == 1){
            if(a != b) unionset(a, b);
        }
        else{
           if(a == b) cout << "YES";
           else cout << "NO";
           cout << '\n';
        }
    }
}