// https://codeforces.com/group/b4CRrS0kmv/contest/412805/problem/Q
#include <bits/stdc++.h>
using namespace std;

#define NAME "KBUILD"
#define int long long
const int N = 2e5 + 5;
const int LOG = 20;
const int INF = 1e9;

/*
cho n đỉnh và n - 1 cạnh (cây) (<= 2e5)
m (<= 2e5) dòng u, v tương ứng đánh dấu mọi đường đi từ u -> v
tìm số cạnh chưa được đánh dấu

Ý tưởng:
    - Gọi cnt[u] là cạnh phía trên u
    - Do đây là cấu trúc cây nên từ u -> v sẽ luôn đi qua lca(u, v)
    - tăng giá trị cạnh u và v, giảm cạnh lca(u, v) đi 2 lần (do những cạnh trên lca(u, v) không thuộc đường đi từ u -> v)
    - Sau khi cập nhật xong, cnt[u] = tổng mọi cnt[v] (với v là con u)
*/

int n, m;
vector<int> adj[N];
int h[N], p[N][LOG + 5], cnt[N];

void dfs(int u, int par){
    for(auto v : adj[u]){
        if(v == par) continue;
        h[v] = h[u] + 1;
        p[v][0] = u;
        dfs(v, u);
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
    if(h[u] < h[v]) swap(u, v);

    int g = h[u] - h[v];
    for(int i = LOG; i >= 0; i--){
        if(g >= (1 << i)){
            u = p[u][i];
            g -= (1 << i);
        }
    }

    if(u == v) return u;

    for(int i = LOG; i >= 0; i--){
        if(p[u][i] != p[v][i]){
            u = p[u][i];
            v = p[v][i];
        }
    }

    return p[u][0];
}

void build(int u, int par){
    for(auto v : adj[u]){
        if(v == par) continue;
        build(v, u);
        cnt[u] += cnt[v]; 
    }
}

void solve()
{  
    cin >> n;
    for(int i = 1; i < n; i++){
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    init();
    cin >> m;
    for(int i = 1; i <= m; i++){
        int u, v; cin >> u >> v;
        cnt[u]++, cnt[v]++, cnt[lca(u, v)]-=2;
    }
    build(1, -1);
    int ans = 0;
    for(int i = 2; i <= n; i++)
        if(cnt[i] == 0) ans++;
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

