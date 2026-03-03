#include <bits/stdc++.h>
using namespace std;

#define int long long
#define NAME "INCSEQ"
const int MAXN = 1e5 + 5;
const int MOD = 1e9 + 7;

int f[102][1002][2], x;
string l, r;

int rec(string s, int idx, int sum, int tight){
    if(idx == s.size()) return sum == x;
    if(f[idx][sum][tight] != -1) return f[idx][sum][tight];
    f[idx][sum][tight] = 0;

    int lim = tight ? s[idx] - '0' : 9;
    for(int i = 0; i <= lim; i++){
        int ntight = tight && i == lim;
        int nsum = sum + i;
        f[idx][sum][tight] = (f[idx][sum][tight] + rec(s, idx + 1, nsum, ntight)) % MOD;
    }

    return f[idx][sum][tight];
}

string low(string s){
    int n = s.size();
    int i = n - 1;

    while(i >= 0){
        if(s[i] > '0'){
            s[i]--;
            break;
        }
        else{
            s[i] = '9';
            i--;
        }
    }

    int pos = 0;
    while(pos + 1 < s.size() && s[pos] == '0')
        pos++;

    return s.substr(pos);
}

void solve(){
    cin >> l >> r >> x;
    memset(f, -1, sizeof(f));
    int b = rec(r, 0, 0, 1);
    
    memset(f, -1, sizeof(f));
    int a = rec(low(l), 0, 0, 1);

    cout << ((b - a) % MOD + MOD) % MOD;
}

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (fopen(NAME ".INP", "r"))
    {
        freopen(NAME ".INP", "r", stdin);
        freopen(NAME ".OUT", "w", stdout);
    }

    int t = 1;
    while(t--){
        solve();
    }
}
