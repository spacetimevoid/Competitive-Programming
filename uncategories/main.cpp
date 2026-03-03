#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e6 + 5;
#define NAME "SERVICE"

int n, k, a[N], b[N], f[N];

void solve() {
    cin >> n >> k;
    for(int i = 1; i <= n; i++) cin >> a[i];
    int d = 0;
    for(int i = 1; i <= n; i++)
        for(int j = a[i] + k; j >= a[i] - k; j--){
            b[++d] = j;
        }

    int len = 0;
    for(int i = 1; i <= d; i++){
        int x = upper_bound(f + 1, f + len + 1, b[i]) - f;
        if(x == len + 1) len++;
        f[x] = b[i];
    }

    cout << len;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    if (fopen(NAME ".INP", "r"))
    {
        freopen(NAME ".INP", "r", stdin);
        freopen(NAME ".OUT", "w", stdout);
    }
    solve();
    return 0;
}
