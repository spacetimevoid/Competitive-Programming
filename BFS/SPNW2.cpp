// https://marisaoj.com/problem/117
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6 + 5;

int n, m;
int dist[MAXN], trace[MAXN];
vector<int> p[MAXN];

// void DFS(int u){
//     visited[u] = true;
//     for(auto v : p[u]){
//         if (visited[v]) continue;
//         DFS(v);
//     }
// }
// DFS Can't find the shortest path

void BFS(int st){
    for(int i = 1; i <= n; i++){
        dist[i] = INT_MAX;
        trace[i] = 0;
    }

    queue<int> q;
    dist[st] = 0;
    q.push(st);

    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(auto v : p[u]){
            if(dist[u] + 1 < dist[v]){
                q.push(v);
                dist[v] = dist[u] + 1;
                trace[v] = u;
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m;
    for(int i = 1; i <= m; i++){
        int u, v; cin >> u >> v;
        p[u].push_back(v);
        p[v].push_back(u);
    }

    memset(dist, 0, sizeof(dist));
    BFS(1);
    cout << dist[n] << '\n';
    
    vector<int> path;
    int pos = n;
    while(pos != 0){
        path.push_back(pos);
        pos = trace[pos];
    }
    reverse(path.begin(), path.end());
    for(auto i : path) cout << i << ' ';
}