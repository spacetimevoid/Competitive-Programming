#include <bits/stdc++.h>
using namespace std;

#define NAME "LCA"
#define int long long
const int N = 1e5 + 5;
const int LOG = 20;
const int INF = 1e9;

int n;
int h[N], p[N][32];
vector<pair<int, int>> adj[N];

void dfs(int u, int par){
    for(auto v : adj[u]){
        if(v.first == par) continue;
        h[v.first] = h[u] + 1;
        p[v.first][0] = u;
        dfs(v.first, u);
    }
}

void init(){
    p[1][0] = 0;
    dfs(1, -1);
    for(int j = 1; j <= LOG; j++)
        for(int i = 1; i <= n; i++)
            p[i][j] = p[p[i][j - 1]][j - 1];
}

int lca(int u, int v){
    if(h[u] < h[v]) 
        swap(u, v);

    int g = h[u] - h[v];
    for(int i = LOG; i >= 0; i--){
        if(g >= (1 << i)){
            u = p[u][i];
            g -= (1 << i);
        }
    }

    if(u == v) 
        return u;

    for(int i = LOG; i >= 0; i--){
        if(p[u][i] != p[v][i]){
            u = p[u][i];
            v = p[v][i];
        }
    }

    return p[u][0];
}

void solve()
{  
    cin >> n;
    for(int i = 1; i < n; i++){
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    init();
    // cout << lca(7, 8);
}

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    if(fopen(NAME ".inp", "r")){
        freopen(NAME ".inp", "r", stdin);
        freopen(NAME ".out", "w", stdout);
    }

    solve ();
}
