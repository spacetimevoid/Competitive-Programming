// https://codeforces.com/group/b4CRrS0kmv/contest/412805/problem/J
#include <bits/stdc++.h>
using namespace std;

#define NAME "UNIMST"
#define int long long
const int N = 3e5 + 5;
const int LOG = 20;
const int INF = 1e9;

struct edge{
    int u, v, w, id;
};

bool cmp(edge x, edge y){
    return x.w > y.w;
}

/*
cho n đỉnh và m cạnh (không nhất thiết liên thông) (<= 1e5)
tìm chu trình có max + min cạnh lớn nhất

Ý tưởng: sử dụng tính chất 2 cây khung lớn nhất
    lấy cạnh không thuộc cây khung + cạnh lớn nhất thuộc cây khung
*/

int n, m;
int lab[N];
bool mark[N], vis[N];
vector<edge> g;
vector<pair<int, int>> p[N];
int h[N], parent[N][LOG + 5], mx[N][LOG + 5];

void dfs(int u, int par){
    vis[u] = true;
    for(auto [v, w] : p[u]){
        if(v == par) continue;
        h[v] = h[u] + 1;
        parent[v][0] = u;
        mx[v][0] = w;
        dfs(v, u);
    }
}

void init(){
    parent[1][0] = 0;
    for(int i = 1; i <= n; i++)
        if(!vis[i])
            dfs(i, -1);
    for(int j = 1; j <= LOG; j++){
        for(int i = 1; i <= n; i++){
            parent[i][j] = parent[parent[i][j - 1]][j - 1];
            mx[i][j] = max(mx[i][j - 1], mx[parent[i][j - 1]][j - 1]);
        }
    }
}

int lca(int u, int v){
    if(h[u] < h[v]) swap(u, v);
    
    int g = h[u] - h[v];
    int MX = 0;
    for(int i = LOG; i >= 0; i--){
        if(g >= (1 << i)){
            MX = max(MX, mx[u][i]);
            u = parent[u][i];
            g -= (1 << i);
        }
    }
    
    if(u == v) return MX;

    for(int i = LOG; i >= 0; i--){
        if(parent[u][i] != parent[v][i]){
            MX = max({MX, mx[u][i], mx[v][i]});
            u = parent[u][i];
            v = parent[v][i];
        }
    }
    
    MX = max({MX, mx[u][0], mx[v][0]});
    
    return MX;
}

int findset(int u){
    return lab[u] < 0 ? u : lab[u] = findset(lab[u]);
}

void unionset(int u, int v, int w){
    if(lab[u] > lab[v]) swap(u, v);
    lab[u] += lab[v];
    lab[v] = u;
}

void solve()
{  
    memset(lab, -1, sizeof(lab));
    cin >> n >> m;
    for(int i = 1; i <= m; i++){
        int u, v, w; cin >> u >> v >> w;
        g.push_back({u, v, w, i});
    }

    sort(g.begin(), g.end(), cmp);

    for(int i = 0; i < g.size(); i++){
        int u = g[i].u, 
            v = g[i].v;
        if(findset(u) != findset(v)){
            unionset(findset(u), findset(v), g[i].w);
            p[u].push_back({v, g[i].w});
            p[v].push_back({u, g[i].w});
            mark[i] = true;
        }
    }

    init();

    int ans = 0;
    for(int i = 0; i < g.size(); i++){
        if(mark[i]) continue;
        int x = lca(g[i].u, g[i].v);
        ans = max(ans, x + g[i].w);
    }

    cout << ans;
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
