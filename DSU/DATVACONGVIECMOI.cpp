#include <bits/stdc++.h>
using namespace std;

#define NAME "main"
#define int long long
const int N = 2e5 + 5;
const int INF = 1e9;

/*
n, m, q (<= 2e5)
n số w[i] (<= 1e9)
m con đường 2 chiều nối u[i] <-> v[i] (<= n)
q truy vấn:
    1. D j <=> xoá con đường thứ j
    2. C i k <=> w[i] = k

? mỗi truy vấn in ra thành phân liên thông có tổng giá trị lớn nhất
ý tưởng:
    1. offline queries, đảo ngược queries (giả sử như đã vượt qua tất cả queries)
    2. dùng một mảng multiset lưu max, khi sửa đáp án ta xoá đáp án cũ xong thêm đáp án mới vào
*/

int n, m, q;
stack<int> w[N];
int lab[N], ans[N];
bool mark[N];
multiset<int> mx;
pair<int, int> adj[N];
pair<char, int> qr[N];

int findset(int u){
    return lab[u] < 0 ? u : lab[u] = findset(lab[u]);
}

void unionset(int u, int v){
    u = findset(u),
    v = findset(v);
    if(u == v) return;
    if(lab[u] > lab[v]) swap(u, v);
    lab[u] += lab[v];
    lab[v] = u;
}

void solve()
{  
    cin >> n >> m >> q;
    for(int i = 1; i <= n; i++){
        int x; cin >> x;
        w[i].push(x);
    }

    for(int i = 1; i <= m; i++)
        cin >> adj[i].first >> adj[i].second;

    for(int i = 1; i <= q; i++){
        char x; int y, z; cin >> x;
        if(x == 'D'){
            cin >> y;
            mark[y] = true;
        }
        else{
            cin >> y >> z;
            w[y].push(z);
        }
        qr[i] = {x, y};
    }
 
    for(int i = 1; i <= n; i++)
        lab[i] = -w[i].top();

    for(int i = 1; i <= m; i++)
        if(!mark[i]) unionset(adj[i].first, adj[i].second);
    for(int i = 1; i <= n; i++)
        mx.insert(-lab[i]);

    for(int i = q; i >= 1; i--){
        ans[i] = *(--mx.end());

        if(qr[i].first == 'D'){
            int u = findset(adj[qr[i].second].first),
                v = findset(adj[qr[i].second].second);
            if(u == v) continue;
            mx.erase(mx.find(-lab[u]));
            mx.erase(mx.find(-lab[v]));
            unionset(adj[qr[i].second].first, adj[qr[i].second].second);
            mx.insert(-lab[findset(adj[qr[i].second].first)]);
        }
        else{
            int u = findset(qr[i].second);
            mx.erase(mx.find(-lab[u]));
            lab[u] += w[qr[i].second].top();
            w[qr[i].second].pop();
            lab[u] -= w[qr[i].second].top();
            mx.insert(-lab[u]);
        }
    }

    for(int i = 1; i <= q; i++)
        cout << ans[i] << '\n';
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