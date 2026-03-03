// https://codeforces.com/group/b4CRrS0kmv/contest/415123/problem/F
#include<bits/stdc++.h>
using namespace std;
const int N = 1005;

/*
m * n (<= 1000)
năm c[i][j] bị ngập (<= 10^9)
k dòng (<= 10^5)
xét các năm a[i] (<= 10^9) -> số mảnh đất còn sót lại

tóm tắt: chỉ xét các năm > a[i], đếm số vùng liên thông
ý tưởng : sử dụng 2 con trỏ - offline queries, với mỗi ô thoả mản điều kiện > a[i] thì xét 4 ô kề cạnh nếu nối được thì nối
*/

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

int n, m, k;
int lab[N * N], ans[N * N];
int c[N][N];
pair<int, int> a[N * N];
vector<tuple<int, int, int>> tp;

int mp(int x, int y){
    return (x - 1) * m + y;
}

int findset(int u){
    return lab[u] < 0 ? u : lab[u] = findset(lab[u]);
}

void unionset(int u, int v){
    if(lab[u] > lab[v]) swap(u, v);
    lab[u] += lab[v];
    lab[v] = u;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(lab, -1, sizeof(lab));
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++){
            cin >> c[i][j];
            tp.push_back({c[i][j], i, j});
        }
    cin >> k;
    for(int i = 1; i <= k; i++){
        cin >> a[i].first;
        a[i].second = i;
    }

    sort(a + 1, a + k + 1, greater<pair<int, int>>());
    sort(tp.begin(), tp.end(), greater<tuple<int, int, int>>());

    int cc = n * m;
    int j = 0;
    for(int i = 1; i <= k; i++){
        while(j < n * m && get<0>(tp[j]) > a[i].first) {
            for(int k = 0; k < 4; k++){
                int x = get<1>(tp[j]) + dx[k],
                    y = get<2>(tp[j]) + dy[k];
                if(x <= 0 || y <= 0 || x > n || y > m || c[x][y] <= a[i].first) continue;
                int u = findset(mp(get<1>(tp[j]), get<2>(tp[j]))),
                    v = findset(mp(x, y));
                if(u != v){
                    cc--;
                    unionset(u, v);
                }
            }
            j++;
        }
        ans[a[i].second] = cc - n * m + j;
    }

    for(int i = 1; i <= k; i++)
        cout << ans[i] << '\n';
}