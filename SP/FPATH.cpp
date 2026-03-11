// https://codeforces.com/group/b4CRrS0kmv/contest/412805/problem/ZB
#include <bits/stdc++.h>
using namespace std;

#define NAME "SP"
#define int long long
const int N = 2e5 + 5;
const int INF = 1e9;

struct edge{
    int u, v, w;
};

bool cmp(edge x, edge y){
    return x.w > y.w;
}

int n, m;
int lab[N];
edge a[N];
int cc = 0;

int findset(int u){
    return lab[u] < 0 ? u : lab[u] = findset(lab[u]);
}

void unionset(int u, int v, int w){
    u = findset(u), v = findset(v);
    if(u == v) return;
    if(lab[u] > lab[v]) swap(u, v);
    lab[u] += lab[v];
    lab[v] = u;
    cc++;
}

void solve()
{  
    memset(lab, -1, sizeof(lab));
    cin >> n >> m;
    for(int i = 1; i <= m; i++)
        cin >> a[i].u >> a[i].v >> a[i].w;

    sort(a + 1, a + m + 1, cmp);

    for(int i = 1; i <= m; i++){
        unionset(a[i].u, a[i].v, a[i].w);
        if(cc == n - 1){
            cout << a[i].w;
            return;
        }
    }
    cout << -1;
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

