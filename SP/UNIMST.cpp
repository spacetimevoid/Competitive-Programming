// https://codeforces.com/group/b4CRrS0kmv/contest/412805/problem/J
#include <bits/stdc++.h>
using namespace std;

#define NAME "UNIMST"
#define int long long
const int N = 2e5 + 5;
const int LOG = 20;
const int INF = 1e9;

/*
cho đồ thị liên thông n đỉnh, m cạnh (<= 2e5)
giá trị của đường đi từ u -> v là trọng số của cạnh lớn nhất
Ta có thể thực hiện thao tác tăng một cạnh lên số +1 vô hạn lần
Tìm số lần thực hiện thao tác ít nhất sao cho có duy nhật 1 đường đi có giá trị bé nhất từ u -> v

Ý tưởng: Tính chất số 1, 2 của cây khung nhỏ nhất
    - tạo cây khung nhỏ nhất (chính là đường đi có giá trị nhỏ nhất từ u -> v)
    - nếu cạnh u, v, w không có trong cây khung
        -> nếu w = giá trị u -> v trong cây khung thì tăng cạnh đó lên
    
    (Sử dụng lca để tối ưu việc tìm trọng số lớn nhất trên cây (LUBENICA))
*/

struct edge{
    int u, v, w;
};

bool cmp(edge x, edge y){
    return x.w < y.w;
}

int n, m;
int lab[N];
int mx_edge = 0;
bool mark[N];
vector<edge> g;
vector<pair<int, int>> p[N];

int h[N], parent[N][LOG + 5], mx[N][LOG + 5];

void dfs(int u, int par){
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
    dfs(1, -1);
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
    int MX = 0, MI = LLONG_MAX;
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

void unionset(int u, int v){
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
        g.push_back({u, v, w});
    }

    sort(g.begin(), g.end(), cmp);

    for(int i = 0; i < g.size(); i++){
        int u = findset(g[i].u),
            v = findset(g[i].v);
        if(u != v){
            unionset(u, v);
            p[u].push_back({v, g[i].w});
            p[v].push_back({u, g[i].w});
            mark[i] = true;
        }
    }

    init();

    int ans = 0;
    for(int i = 0; i < g.size(); i++){
        if(mark[i]) continue;
        if(lca(g[i].u, g[i].v) == g[i].w) ans++;
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
