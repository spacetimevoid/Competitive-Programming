// https://codeforces.com/group/b4CRrS0kmv/contest/412805/problem/T
#include <bits/stdc++.h>
using namespace std;

#define NAME "LUBENICA"
#define int long long
const int N = 2e5 + 5;
const int LOG = 20;
const int INF = 1e9;

/*
cho n đỉnh và n - 1 cạnh (cây)
q truy vấn u, v
tìm trọng số bé nhất và lớn nhất trên đường đi từ u -> v

Ý tưởng: 
    - mảng mx[i][j] tương tự mảng p[i][j] là giá trị W lớn nhất cách đỉnh i 2^j đỉnh
        mx[i][j] = max(mx[i][j - 1], mx[p[i][j - 1]][j - 1]);

    Bây giờ với mỗi truy vấn ta chỉ cần cập nhật max trên đường đi bằng lca
    Tương tự với min[i][j]
*/

int n;
vector<pair<int, int>> adj[N];
int h[N], p[N][LOG + 5], mx[N][LOG + 5], mi[N][LOG + 5];

void dfs(int u, int par){
    for(auto [v, w] : adj[u]){
        if(v == par) continue;
        h[v] = h[u] + 1;
        p[v][0] = u;
        mx[v][0] = w;
        mi[v][0] = w;
        dfs(v, u);
    }
}

void init(){
    p[1][0] = 0;
    dfs(1, -1);
    for(int j = 1; j <= LOG; j++){
        for(int i = 1; i <= n; i++){
            p[i][j] = p[p[i][j - 1]][j - 1];
            mx[i][j] = max(mx[i][j - 1], mx[p[i][j - 1]][j - 1]);
            mi[i][j] = min(mi[i][j - 1], mi[p[i][j - 1]][j - 1]);
        }
    }
}

int lca(int u, int v){
    if(h[u] < h[v]) swap(u, v);
    
    int g = h[u] - h[v];
    int MX = 0, MI = LLONG_MAX;
    for(int i = LOG; i >= 0; i--){
        if(g >= (1 << i)){
            MX = max(MX, mx[u][i]);
            MI = min(MI, mi[u][i]);
            u = p[u][i];
            g -= (1 << i);
        }
    }
    
    if(u == v) {
        cout << MI << ' ' << MX << '\n';
        return u;
    }

    for(int i = LOG; i >= 0; i--){
        if(p[u][i] != p[v][i]){
            MX = max({MX, mx[u][i], mx[v][i]});
            MI = min({MI, mi[u][i], mi[v][i]});
            u = p[u][i];
            v = p[v][i];
        }
    }
    
    MX = max({MX, mx[u][0], mx[v][0]});
    MI = min({MI, mi[u][0], mi[v][0]});
    
    cout << MI << ' ' << MX << '\n';

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
    int q; cin >> q;
    while(q--){
        int u, v; cin >> u >> v;
        lca(u, v);
    }
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
