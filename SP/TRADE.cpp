// https://codeforces.com/group/b4CRrS0kmv/contest/412805/problem/ZE
#include <bits/stdc++.h>
using namespace std;

#define NAME "TRADE"
#define int long long
const int N = 5e5 + 5;
const int INF = 1e9;

/*
cho n đỉnh m cạnh (<= 5e5)
k giá trị x[i] 
tìm cách sao cho một đỉnh bất kì luôn cùng tplt với ít nhất một đỉnh thuộc tập x

Ý tưởng:
    C1: Tạo đỉnh ảo là tổng cửa hàng nối tất cả cửa hàng con, sau đó MST
    C2: Sử dụng MST, nếu 2 tplt đều đã chứa cửa hàng thì không nối
*/

struct edge{
    int u, v, w;
};

bool cmp(edge x, edge y){
    return x.w < y.w;
}

int n, m, k;
int x[N];
vector<edge> adj;
int lab[N];
int ans = 0;

int findset(int u){
    return lab[u] <= 0 ? u : lab[u] = findset(lab[u]);
}

void unionset(int u, int v){
    lab[u] = max(lab[u], lab[v]);
    lab[v] = u;
}

void solve()
{  
    memset(lab, -1, sizeof(lab));
    cin >> n >> m >> k;
    for(int i = 1; i <= k; i++) {
        cin >> x[i];
        lab[x[i]] = 0;
    }
    for(int i = 1; i <= m; i++){
        int u, v, w; cin >> u >> v >> w;
        adj.push_back({u, v, w});
    }

    sort(adj.begin(), adj.end(), cmp);
    for(auto i : adj){
        int x = findset(i.u),
            y = findset(i.v);
        if(x != y && (lab[x] == -1 || lab[y] == -1)){
            unionset(x, y);
            ans += i.w;
        }
    }

    for(int i = 1; i <= n; i++){
        if(lab[findset(i)] == -1){
            cout << -1;
            return;
        }
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
