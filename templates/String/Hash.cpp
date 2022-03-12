mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
 
struct Hash{
    int n, p, mod;
    vector<int> h, pw;
    void init(string &s, int _p, int _mod){
        n = s.size();
        p = _p, mod = _mod;
        h.resize(n + 1), pw.resize(n);
        pw[0] = 1;
        for(int i = 1; i < n; i++)pw[i] = pw[i - 1] * p % mod;
        for(int i = 0; i < n; i++){
            h[i + 1] = (h[i] * p % mod + s[i]) % mod;
        }
    }
    int get(int l, int r){
        return (h[r + 1] - h[l] * pw[r - l + 1] % mod + mod) % mod;
    }
};
