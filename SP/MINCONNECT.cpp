// https://codeforces.com/group/b4CRrS0kmv/contest/412805/problem/L
#include <bits/stdc++.h>
using namespace std;

#define NAME "MINCONNECT"
#define int long long
const int N = 1e5 + 5;
const int INF = 1e9;

/*
cho n đỉnh và m cạnh vô hướng (<= 1e5)
x[i] là giá trị đỉnh i
trọng số của một tplt con của đồ thị ban đầu là min tất các đỉnh
k = 1...n in ra trọng số lớn nhất của những tplt có đúng k đỉnh

Ý tưởng: Tương tự bài bears DSU
    (Xét từng x <=> với những đỉnh có trọng số không bé hơn x ta được độ dài lớn nhất là)
*/

int n, m;
int lab[N];
pair<int, int> x[N];
vector<int> adj[N];
bool mark[N];
int ans[N];
int num = 1;

int findset(int u){
    return lab[u] < 0 ? u : lab[u] = findset(lab[u]);
}

void unionset(int u, int v){
    u = findset(u), v = findset(v);
    if(u == v) return;
    lab[u] += lab[v];
    lab[v] = u;
    num = max(num, -lab[u]);
}

void solve()
{  
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        cin >> x[i].first;
        x[i].second = i;
    }

    for(int i = 1; i <= m; i++){
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    memset(ans, -1, sizeof(ans));
    memset(lab, -1, sizeof(lab));
    sort(x + 1, x + n + 1, greater<pair<int, int>>());

    int j = 1;
    for(int i = 1; i <= n; i++){
        int u = x[i].second;
        for(auto v : adj[u]){
            if(mark[v])
                unionset(u, v);
        }
        mark[u] = true;
        while(j <= num){
            ans[j] = x[i].first;
            j++;
        }
    }

    for(int i = 1; i <= n; i++){
        cout << ans[i] << ' ';
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
