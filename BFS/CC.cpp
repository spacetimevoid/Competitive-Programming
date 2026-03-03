// https://marisaoj.com/problem/115
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6 + 5;

bool visited[MAXN];
vector<int> p[MAXN];

void DFS(int u){
    visited[u] = true;
    for(auto v : p[u]){
        if (visited[v]) continue;
        DFS(v);
    }
}

void BFS(int st){
    queue<int> q;
    visited[st] = true;
    q.push(st);

    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(auto v : p[u]){
            if(visited[v]) continue;
            q.push(v);
            visited[v] = true;
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= m; i++){
        int u, v; cin >> u >> v;
        p[u].push_back(v);
        p[v].push_back(u);
    }

    int CC = 0;
    for(int i = 1; i <= n; i++){
        if(visited[i]) continue;
        // BFS(i);
        // or
        // DFS(i);
        CC++;
    }

    cout << CC;
}