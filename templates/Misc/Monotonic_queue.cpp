#include <bits/stdc++.h>
using namespace std;
#define int long long // a.k.a. TLE creator
#define all(x) x.begin(), x.end()
template<class A, class B> istream& operator >>(istream &o, pair<A, B> &x){return o >> x.first >> x.second;}
template<class A, class B> ostream& operator <<(ostream &o, pair<A, B> &x){return o << x.first << ' ' << x.second << ' ';}
void setIO(){ios::sync_with_stdio(false); cin.tie(0);}
const int INF = 2e18, MOD = 998244353, N = 1e6 + 2, K = __lg(N) + 1;

struct line{
    int m, c, idx;// mx + c
    int operator ()(const int x){return m * x + c;}
};

signed main(){
    setIO();
    int n, k, b;
    cin >> n >> k >> b;
    int a[n];
    for(int &i : a)cin >> i;
    vector<int> dp(n);
    deque<line> dq;
    dp[0] = a[0];
    dq.push_back({0, dp[0], 0});
    auto intersect = [&](line x, line y, line now){
        // c_2 - c_1 / m_1 - m_2
        /*
         now * y = y.c - now.c / now.m - y.m
         x * y = x.c - y.c / y.m - x.m
         x expire = x.idx + k
         return now * y <= x * y && now * y <= x expire
         */
        return (y.c - now.c) * (y.m - x.m) <= (now.m - y.m) * (x.c - y.c) && (y.c - now.c) <= (now.m - y.m) * (x.idx + k);
    };
    for(int i = 1; i < n; i++){
        while(!dq.empty() && dq.front().idx < i - k)
            dq.pop_front();
        while(dq.size() >= 2 && dq[0](i) <= dq[1](i))
            dq.pop_front();
        dp[i] = dq[0](i) + a[i] - i * i * b;
        line now = {2 * i * b, dp[i] - i * i * b, i};
        while(dq.size() >= 2 && intersect(dq[(int)dq.size() - 2], dq.back(), now))
            dq.pop_back();
        dq.push_back(now);
    }
    cout << dp[n - 1];
}
