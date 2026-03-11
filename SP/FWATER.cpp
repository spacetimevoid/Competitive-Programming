// https://codeforces.com/group/b4CRrS0kmv/contest/412805/problem/D
#include <bits/stdc++.h>
using namespace std;

#define NAME "FWATER"
#define int long long
const int N = 4e5 + 5;
const int INF = 1e9;

/*
n, m
n giá trị đào giếng w[i]
m cạnh u, v trọng số p
Có 2 thao tác:
    1. đào giếng với chi phí w[i]
    2. nối cạnh u, v chi phí p
Chi phí ít nhất để mỗi node bất kì thuộc một vùng liên thông có giếng

Ý tưởng : 
    1. tạo một đỉnh ảo là nguồn nước chính chảy về giếng
        {i, n + 1, w[i]}
    2. tìm cây khung nhỏ nhất
*/

struct edge{
    int u, v, p;
};

bool cmp(edge x, edge y){
    return x.p < y.p;
}

int n, m;
edge a[N];
int w[N];
int lab[N];
int ans = 0;

int findset(int u){
    return lab[u] < 0 ? u : lab[u] = findset(lab[u]);
}

void unionset(int u, int v, int p){
    u = findset(u), v = findset(v);
    if(u == v) return;
    if(lab[u] > lab[v]) swap(u, v);
    ans += p;
    lab[u] += lab[v];
    lab[v] = u;
}

void solve()
{  
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        cin >> w[i];
    }
    for(int i = 1; i <= m; i++)
        cin >> a[i].u >> a[i].v >> a[i].p;

    for(int i = m + 1; i <= m + n; i++)
        a[i].u = i - m, a[i].v = n + 1, a[i].p = w[i - m];
    
    memset(lab, -1, sizeof(lab));
    sort(a + 1, a + m + n + 1, cmp);

    for(int i = 1; i <= m + n; i++)
        unionset(a[i].u, a[i].v, a[i].p);

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

