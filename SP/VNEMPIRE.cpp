// https://codeforces.com/group/b4CRrS0kmv/contest/412805/problem/F
#include <bits/stdc++.h>
using namespace std;

#define NAME "VNEMPIRE"
#define int long long
const int N = 1e5 + 5;
const int INF = 1e9;

/*
Cho n đỉnh
mỗi đỉnh có 3 số x, y, z
nếu đối đỉnh a và b thì mất chi phí min({|xa - xb|, |ya - yb|, |ya - yb|})
tìm chi phí nhỏ nhất để n đỉnh này thuộc cùng 1 tplt

ý tưởng: 
    1. sort lại mảng theo x, theo y, theo z tăng dần
    2. dễ dàng nhận thấy 2 giá trị càng gần nhau thì càng bé (do MST chỉ quan tâm trọng số càng bé càng tốt nên ta chỉ cần xét 2 giá trị liền nhau)
        -> bỏ x[i] - x[i - 1], y[i] - y[i - 1], z[i] - z[i - 1] vào mảng tượng trưng cho trọng số giữa 2 nút u, v
        -> sort lại mảng adj
        (do giá trị nhỏ hơn sẽ đứng trước nên sẽ không mất tính tổng quát của min({|xa - xb|, |ya - yb|, |ya - yb|}))
    3. sử dụng MST

*/

struct edge{
    int u, v, w;
};

bool cmp(edge x, edge y){
    return x.w < y.w;
}

int n;
int ans = 0;
int lab[N];
vector<edge> adj;
pair<int, int> x[N], y[N], z[N];

int findset(int u){
    return lab[u] < 0 ? u : lab[u] = findset(lab[u]);
}

void unionset(int u, int v, int w){
    u = findset(u), v = findset(v);
    if(u == v) return;
    if(lab[u] > lab[v]) swap(u, v);
    lab[u] += lab[v];
    lab[v] = u;
    ans += w;
}

void solve()
{  
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> x[i].first >> y[i].first >> z[i].first;
        x[i].second = y[i].second = z[i].second = i;
    }

    memset(lab, -1, sizeof(lab));

    sort(x + 1, x + n + 1);
    sort(y + 1, y + n + 1);
    sort(z + 1, z + n + 1);

    for(int i = 2; i <= n; i++){
        adj.push_back({x[i].second, x[i - 1].second, x[i].first - x[i - 1].first});
        adj.push_back({y[i].second, y[i - 1].second, y[i].first - y[i - 1].first});
        adj.push_back({z[i].second, z[i - 1].second, z[i].first - z[i - 1].first});
    }

    sort(adj.begin(), adj.end(), cmp);

    for(auto i : adj)
        unionset(i.u, i.v, i.w);

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

