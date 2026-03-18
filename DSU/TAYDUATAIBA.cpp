#include <bits/stdc++.h>
using namespace std;

#define NAME "main"
#define int long long
const int N = 2e5 + 5;
const int INF = 1e9;

/*
n đỉnh
m cạnh 2 chiều
(n, m <= 2e5)
h[i] là giá trị của n đỉnh
q truy vấn
u, v, c

chi phí đi từ đỉnh i -> j là hi - hj
c = c + hi - hj

tìm đường đi từ u -> v sao cho c luôn >- 0
nếu có in YES không in NO

Ý tưởng:
    Ta nhận thấy chi phí đi từ đỉnh u -> ... -> v mất chi phí
        c + h[u] - h[v]
    do những đỉnh ở giữa triệt tiêu lẫn nhau

    -> chỉ cần mọi đỉnh x trên đường đi từ u -> .... -> v thoả mãn
        c + h[u] - h[x] >= 0
        
    Sử dụng offline queries

*/

struct query{
    int u, v, c, val, id;
};
int n, m;
pair<int, int> h[N];
vector<int> adj[N];
vector<query> qr;
int q;
int ans[N];

bool cmp(query x, query y){
    return x.val < y.val;
}

int lab[N];
bool mark[N];

int findset(int u){
    return lab[u] < 0 ? u : lab[u] = findset(lab[u]);
}
void unionset(int u, int v){
    u = findset(u), v = findset(v);
    if(u == v) return;
    if(lab[u] > lab[v]) swap(u, v);
    lab[u] += lab[v];
    lab[v] = u;
}

void solve()
{  
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        cin >> h[i].first;
        h[i].second = i;
    }
    
    for(int i = 1; i <= m; i++){
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    cin >> q;
    for(int i = 1; i <= q; i++){
        int u, v, c; cin >> u >> v >> c;
        qr.push_back({u, v, c, h[u].first + c, i});
    }

    memset(lab, -1, sizeof(lab));
    sort(qr.begin(), qr.end(), cmp);
    sort(h + 1, h + n + 1);

    int j = 1;
    for(int i = 0; i < q; i++){
        while(j <= n && qr[i].val >= h[j].first){
            for(auto k : adj[h[j].second]){
                if(mark[k]) unionset(h[j].second, k);
            }
            mark[h[j].second] = true;
            j++;
        }
        ans[qr[i].id] = (findset(qr[i].u) == findset(qr[i].v));
    }

    for(int i = 1; i <= q; i++){
        if(ans[i]) cout << "YES\n";
        else cout << "NO\n";
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