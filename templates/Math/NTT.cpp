const MOD = 998244353;

int mypow(int a, int k){
    if(!a)return 0;
    int ans = 1;
    for(; k; k >>= 1, a = a * a % MOD)
        if(k & 1)ans = ans * a % MOD;
    return ans;
}

void NTT(vector<int> &a, bool inv = false){
    int n = a.size();
    for(int i = 1, j = 0; i < n; i++){
        int bit = n >> 1;
        for(; bit & j; bit >>= 1)
            j ^= bit;
        j ^= bit;
        if(i < j)swap(a[i], a[j]);
    }
    int p = mypow(3, (MOD - 1) / n);
    int prt = (inv ? mypow(p, MOD - 2) : p);
    for(int len = 2; len <= n; len <<= 1){
        int rot = mypow(prt, n / len);
        for(int i = 0; i < n; i += len){
            int w = 1;
            for(int j = 0; j < len / 2; j++){
                int u = a[i + j], v = a[i + j + len / 2] * w % MOD;
                a[i + j] = u + v;
                if(a[i + j] > MOD)a[i + j] -= MOD;
                a[i + j + len / 2] = u - v;
                if(a[i + j + len / 2] < 0)a[i + j + len / 2] += MOD;
                w = w * rot % MOD;
            }
        }
    }
    if(inv){
        int div = mypow(n, MOD - 2);
        for(int &i : a)(i *= div) %= MOD;
    }
}

int lg(int a){return 63 - __builtin_clzll(a);}

void mul(vector<int> &a, vector<int> &b){
    int nm = a.size() + b.size() - 1;
    int len = 1 << lg(nm) + 1;
    a.resize(len);
    b.resize(len);
    NTT(a), NTT(b);
    for(int i = 0; i < len; i++)a[i] = a[i] * b[i] % MOD;
    NTT(a, true);
    a.resize(nm);
}
