// https://codeforces.com/group/b4CRrS0kmv/contest/412805/problem/I
#include <bits/stdc++.h>
using namespace std;

#define NAME "UNIMST"
#define int long long
const int N = 2e3 + 5;
const int INF = 1e9;

/*
cho đồ thị liên thông n đỉnh, m cạnh (<= 2e3)
giá trị của đường đi từ u -> v là trọng số của cạnh lớn nhất
Ta có thể thực hiện thao tác tăng một cạnh lên số +1 vô hạn lần
Tìm số lần thực hiện thao tác ít nhất sao cho có duy nhật 1 đường đi có giá trị bé nhất từ u -> v

Ý tưởng: Tính chất số 1, 2 của cây khung nhỏ nhất
    - tạo cây khung nhỏ nhất (chính là đường đi có giá trị nhỏ nhất từ u -> v)
    - nếu cạnh u, v, w không có trong cây khung
        -> nếu w = giá trị u -> v trong cây khung thì tăng cạnh đó lên
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
vector<edge> adj;
vector<pair<int, int>> p[N];

int findset(int u){
    return lab[u] < 0 ? u : lab[u] = findset(lab[u]);
}

void unionset(int u, int v){
    if(lab[u] > lab[v]) swap(u, v);
    lab[u] += lab[v];
    lab[v] = u;
}

bool dfs(int u, int des, int par){
    if(u == des) return true;
    for(auto v : p[u]){
        if(v.first == par) continue;
        if(dfs(v.first, des, u)){
            mx_edge = max(mx_edge, v.second);
            return true;
        }
    }
    return false;
}

void solve()
{  
    memset(lab, -1, sizeof(lab));
    cin >> n >> m;
    for(int i = 1; i <= m; i++){
        int u, v, w; cin >> u >> v >> w;
        adj.push_back({u, v, w});
    }

    sort(adj.begin(), adj.end(), cmp);

    for(int i = 0; i < adj.size(); i++){
        int u = adj[i].u, 
            v = adj[i].v;
        if(findset(u) != findset(v)){
            unionset(findset(u), findset(v));
            p[u].push_back({v, adj[i].w});
            p[v].push_back({u, adj[i].w});
            mark[i] = true;
        }
    }

    int ans = 0;
    for(int i = 0; i < adj.size(); i++){
        if(mark[i]) continue;
        mx_edge = 0;
        dfs(adj[i].u, adj[i].v, -1);
        if(mx_edge == adj[i].w) ans++;
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
