// https://codeforces.com/group/b4CRrS0kmv/contest/415123/problem/M
#include <bits/stdc++.h>
using namespace std;

#define NAME "main"
#define int long long
const int N = 1e3 + 5;
const int INF = 1e9;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, -1, 0, 1};

/*
n, m (<= 1e3)
a[i][j] (<= 1e4)

1. a[1][1] = 1
2. các vùng liên thông là các vùng có cùng giá trị
3. chi phí biến giá trị một vùng liên thông thành giá trị 1 là:
    giá trị ban đầu * số lượng phần tử

Tìm tổng chi phí bé nhất để a[1][1] và a[n][m] thuộc 1 vùng liên thông

Ý tưởng: biến những vùng liên thông thành node của đồ thị, sử dụng dijikstra tính toán chi phí
*/

int n, m;
int a[N][N];
int lab[N * N];
vector<int> adj[N * N];

int findset(int u){
    return lab[u] <= 0 ? u : lab[u] = findset(lab[u]);
}

void unionset(int u, int v){
    u = findset(u), v = findset(v);
    if(u > v) swap(u, v);
    if(u == v) return;
    lab[u] += lab[v];
    lab[v] = u; 
}

int mp(int x, int y){
    return m * (x - 1) + y;
}

priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
int dist[N * N];
void djk(){
    for(int i = 1; i <= n * m; i++)
        dist[i] = LLONG_MAX;
    dist[1] = 0;
    pq.push({0, 1});
    while(!pq.empty()){
        pair<int, int> u = pq.top();
        pq.pop();
        if(u.first > dist[u.second]) continue;
        for(auto v : adj[u.second]){
            if(dist[v] > dist[u.second] - lab[v]){
                dist[v] = dist[u.second] - lab[v];
                pq.push({dist[v], v});
            }
        }
    }
}

void solve()
{  
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++){
            cin >> a[i][j];
            lab[mp(i, j)] = (a[i][j] == 1) ? 0 : -a[i][j];
        }
    
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++){
            for(int k = 0; k < 4; k++){
                int x = i + dx[k],
                    y = j + dy[k];
                if(x <= 0 || x > n || y <= 0 || y > m || a[i][j] != a[x][y]) continue;
                unionset(mp(i, j), mp(x, y));
            }
        }

    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++){
            for(int k = 0; k < 4; k++){
                int x = i + dx[k],
                    y = j + dy[k];
                if(x <= 0 || x > n || y <= 0 || y > m || a[i][j] == a[x][y]) continue;
                int u = findset(mp(i, j)),
                    v = findset(mp(x, y));
                adj[u].push_back(v);
            }
        }

    djk();
    cout << dist[findset(n * m)];
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