// https://codeforces.com/group/b4CRrS0kmv/contest/415123/problem/L
#include <bits/stdc++.h>
using namespace std;

#define NAME "main"
#define int long long
const int N = 3e6 + 5;
const int INF = 1e9;

/*
n (<= 3e6), m (<= 5e5)
l[i], r[i] có cha là xi (không ghi đè) (n giá trị)

tóm tắt : với mỗi i thì đặt đoạn từ l[i] -> r[i] = x[i] (trừ x[i] ra) nếu đã được đặt rồi thì bỏ qua
ý tưởng : findset(l) để tìm phần tử gần l nhất chưa được xử lý -> rồi gắn cha
*/

int n, m;
int lab[N], ans[N];

int findset(int u){
    return lab[u] < 0 ? u : lab[u] = findset(lab[u]);
}

void unionset(int u, int v){
    // if(lab[u] > lab[v]) swap(u, v);
    lab[v] += lab[u];
    lab[u] = v;
}

void solve()
{  
    memset(lab, -1, sizeof(lab));
    cin >> n >> m;
    for(int i = 1; i <= m; i++){
        int l, r, x; cin >> l >> r >> x;
        while(l <= r){
            l = findset(l);
            if(l > r) break;
            if(l == x) l++;
            else{
                ans[l] = x;
                unionset(l, findset(l + 1));
            }
        }
    }

    for(int i = 1; i <= n; i++)
        cout << ans[i] << ' ';
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