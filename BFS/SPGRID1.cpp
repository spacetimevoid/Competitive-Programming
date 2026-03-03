// https://marisaoj.com/problem/119
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e3 + 5;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

int n, m;
char a[MAXN][MAXN];
int dist[MAXN][MAXN];

// void DFS(int u){
//     visited[u] = true;
//     for(auto v : p[u]){
//         if (visited[v]) continue;
//         DFS(v);
//     }
// }
// DFS Can't find the shortest path

void BFS(){
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            dist[i][j] = INT_MAX;

    queue<pair<int,int>> q;
    dist[1][1] = 0;
    q.push({1, 1});

    while(!q.empty()){
        pair<int,int> u = q.front();
        q.pop();
        
        for(int i = 0; i < 4; i++){
            pair<int, int> v = {u.first + dx[i], u.second + dy[i]};
            if(v.first <= 0 || v.first > n || v.second <= 0 || v.second > m || a[v.first][v.second] == '1') continue;
            if(dist[u.first][u.second] + 1 < dist[v.first][v.second]){
                dist[v.first][v.second] = dist[u.first][u.second] + 1;
                q.push(v);
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            cin >> a[i][j];
    
    BFS();
    if (dist[n][m] == INT_MAX) cout << -1;
    else cout << dist[n][m];
}