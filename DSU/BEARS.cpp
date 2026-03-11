// https://codeforces.com/group/b4CRrS0kmv/contest/415123/problem/L
#include <bits/stdc++.h>
using namespace std;

#define NAME "BEAR"
#define int long long
const int N = 1e5 + 5;
const int INF = 1e9;

/*
n (<= 1e5)
ai (1 -> 1e9)
F(i, j) = phần tử bé nhất từ i -> j
Với mỗi x từ 1 -> n in ra F(i, i + x - 1) lớn nhất

ý tưởng 1 : gọi l[i] và r[i] và phần tử đầu tiên bé hơn a[i] ở bên trái và phải
ý tưởng 2 : 
    1. sort a[i] theo thứ tự giảm dần
    2. với mỗi a[i] tạo thành phân liên thông từ 2 phần tử xung quanh sao cho a[i] là bé nhất.
    -> những độ dài nào <= cc sẽ có gía trị bé nhất là a[i] là lớn nhất
*/

int n;
pair<int, int> a[N];

int l[N], r[N], f[N];
stack<int> st;
namespace c1{
    void solve(){
        for(int i = 1; i <= n; i++){
            while(!st.empty() && a[i].first <= a[st.top()].first) 
                st.pop();
            if(st.empty()) l[i] = 0;
            else l[i] = st.top();
            st.push(i);
        }
    
        while(!st.empty()) st.pop();
    
        for(int i = n; i >= 1; i--){
            while(!st.empty() && a[i].first <= a[st.top()].first) 
                st.pop();
            if(st.empty()) r[i] = n + 1;
            else r[i] = st.top();
            st.push(i);
        }
    
        for(int i = 1; i <= n; i++)
            f[r[i] - l[i] - 1] = max(f[r[i] - l[i] - 1], a[i].first);
    
        for(int i = n - 1; i >= 1; i--){
            f[i] = max(f[i + 1], f[i]);
        }
    
        for(int i = 1; i <= n; i++)
            cout << f[i] << ' ';
    }
};


int lab[N], mark[N];
int ans[N]; 
int cc = 1, j = 0;
namespace c2{
    int findset(int u){
        return lab[u] < 0 ? u : lab[u] = findset(lab[u]);
    }

    void unionset(int u, int v){
        u = findset(u), v = findset(v);
        if(u == v) return;
        lab[u] += lab[v];
        lab[v] = u;
        cc = max(cc, -lab[u]);
    }
    
    void solve(){
        memset(lab, -1, sizeof(lab));
        sort(a + 1, a + n + 1, greater<pair<int, int>>());
        for(int i = 1; i <= n; i++){
            mark[a[i].second] = true;
            if(a[i].second - 1 > 0 && mark[a[i].second - 1])
                unionset(a[i].second - 1, a[i].second);
            if(a[i].second + 1 <= n && mark[a[i].second + 1])
                unionset(a[i].second + 1, a[i].second);
            if(j < cc){
                for(int k = j + 1; k <= cc; k++)
                    ans[k] = a[i].first;
                j = cc;
            }
        }

        for(int i = 1; i <= n; i++)
            cout << ans[i] << ' ';
    }
};

void solve()
{  
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> a[i].first;
        a[i].second = i;
    }

    // c1::solve();
    // c2::solve();
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
