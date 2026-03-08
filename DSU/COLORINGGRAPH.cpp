// https://codeforces.com/group/b4CRrS0kmv/contest/415123/problem/N
#include <bits/stdc++.h>
using namespace std;

#define NAME "main"
#define int long long
const int N = 2e5 + 5;
const int INF = 1e9;

/*
n, m
n số c[i] là màu nút i
m dòng u, v là cạnh vô hướng nối u và v
với mỗi truy vấn in ra số lượng cặp (i, j) sao cho i, j cùng màu và cùng 1 thành phần liên thông

Ý tưởng: Small to large
    1. Mỗi thành phần liên thông lưu:
        - Màu
        - Số lượng phần tử có màu đó
    2. Unionset
        Gộp nhỏ vào lớn
        ANS = ANS - tổ hợp chập 2 của node u - tổ chập 2 của node v + tổ chập 2 của u hợp v
    Gợi ý sử dụng map<int, int> node[N]
*/

int n, m;
int c[N];
int lab[N];
map<int, int> node[N];
int ans = 0;

int cal(int n){
    return n * (n - 1) / 2;
}

int findset(int u){
    return lab[u] < 0 ? u : lab[u] = findset(lab[u]);
}

void unionset(int u, int v){
    u = findset(u), v = findset(v);
    if(u == v) return;
    if(lab[u] > lab[v]) swap(u, v);
    lab[u] += lab[v];
    lab[v] = u;
    
    for(auto i : node[v]){
        int color = i.first,
            num = i.second;
        ans -= cal(num);
        ans -= cal(node[u][color]);
        node[u][color] += num;
        ans += cal(node[u][color]);
    }
    node[v].clear();
} 

void solve()
{  
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        cin >> c[i];
        node[i][c[i]] = 1;
    }

    memset(lab, -1, sizeof(lab));
    while(m--){
        int u, v; cin >> u >> v;
        unionset(u, v);
        cout << ans << '\n';
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