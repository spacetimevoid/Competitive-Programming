// https://codeforces.com/group/b4CRrS0kmv/contest/412805/problem/F
#include <bits/stdc++.h>
using namespace std;

#define NAME "CFULLC"
#define int long long
const int N = 1e6 + 5;
const int INF = 1e9;

/*
n đỉnh, m cạnh (<= 1e6)
x[i] (<= 1e9) chi phí của đỉnh i để nối với một đỉnh khác
    -> nối u với v thì mất x[u] + x[v]
tìm chi phí ít nhất để n cạnh này liên thông

Ý tưởng: sau m cạnh ta được các thành phần liên thông
    -> chỉ cần tìm giá trị đỉnh có chi phí nhỏ nhất (cố định), nối đỉnh đó với nút có giá trị nhỏ nhất ở những vùng liên thông khác
*/

int n, m;
int x[N];
int lab[N];
int ans = 0;

int findset(int u){
    return lab[u] < 0 ? u : lab[u] = findset(lab[u]);
}

void unionset(int u, int v){
    lab[u] = max(lab[u], lab[v]);
    lab[v] = u;
}

void solve()
{  
    int mi_node = 1;
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        cin >> x[i];
        lab[i] = -x[i];
        if(x[mi_node] > x[i]) mi_node = i;
    }

    for(int i = 1; i <= m; i++){
        int u, v; cin >> u >> v;
        int x = findset(u),
            y = findset(v);
        if(x != y)
            unionset(x, y);
    }

    for(int i = 1; i <= n; i++){
        int x = findset(mi_node),
            y = findset(i);
        if(x != y){
            ans -= lab[x] + lab[y];
            unionset(x, y);
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

