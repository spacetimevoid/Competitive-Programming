// https://codeforces.com/group/b4CRrS0kmv/contest/412805/problem/G
#include <bits/stdc++.h>
using namespace std;

#define NAME "CHONDUONG"
#define int long long
const int N = 505;
const int INF = 1e9;

/*
cho n đỉnh (<= 500), m cạnh (<= 5e4)
mỗi lần nhập u, v, w thì tìm cây khung tại thời điểm đó (dynamic mst)

Ý tưởng: O(n * m)
    - Nếu u, v cùng tplt -> nối u, v
    - Ngược lại:
        1. Đồ thị sẽ tạo chu trình -> sử dụng tính chất số 1 của cây khung
        2. Nếu trọng số cạnh lớn nhất từ u -> v trong cây khung > trọng số cạnh u, v mới
            - xoá cạnh cũ trong cây (chỉ cần xoá mảng adj bởi vì dsu chỉ kiểm tra cùng tplt)
            - cập nhật cạnh mới
    (Thuật toán chuẩn O(m * log(n)))
*/

int n, m;
int lab[N];
vector<pair<int, int>> adj[N];
tuple mx_edge = {0, 0, 0};

int findset(int u){
    return lab[u] < 0 ? u : lab[u] = findset(lab[u]);
}

void unionset(int u, int v){
    if(lab[u] > lab[v]) swap(u, v);
    lab[u] += lab[v];
    lab[v] = u;
}

bool DFS(int u, int par, int en){
    if(u == en) return true;
    for(auto v : adj[u]){
        if(v.first == par) continue;

        if(DFS(v.first, u, en)){
            if(get<2>(mx_edge) < v.second)
                mx_edge = {u, v.first, v.second};
            return true;
        }
    }
    return false;
}

void del(int x, vector<pair<int, int>> &y){
    for(int i = 0; i < y.size(); i++){
        if(y[i].first == x){
            y.erase(y.begin() + i);
            break;
        }
    }
}

void solve()
{  
    memset(lab, -1, sizeof(lab));
    cin >> n >> m;
    int cc = n, ans = 0;
    for(int i = 1; i <= m; i++){
        int u, v, w; cin >> u >> v >> w;
        int x = findset(u),
            y = findset(v);

        if(x != y){
            unionset(x, y);
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
            ans += w; 
            cc--;
        }
        else{
            mx_edge = {0, 0, 0};
            DFS(u, -1, v);
            if(get<2>(mx_edge) > w){
                del(get<0>(mx_edge), adj[get<1>(mx_edge)]);
                del(get<1>(mx_edge), adj[get<0>(mx_edge)]);
                adj[u].push_back({v, w});
                adj[v].push_back({u, w});
                ans -= get<2>(mx_edge) - w;
            }
        }

        if(cc == 1)
            cout << ans << '\n';
        else 
            cout << -1 << '\n';
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

