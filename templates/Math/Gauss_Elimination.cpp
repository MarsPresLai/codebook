int mod;

int mypow(int a, int k){
    int ans = 1;
    for(; k; k >>= 1, a = a * a % mod){
        if(k & 1)ans = ans * a % mod;
    }
    return ans;
}

struct gauss{
    vector<vector<int>> m;
    vector<int> val;
    int n;
    gauss(int _n) : n(_n){
        m.resize(n, vector<int> (n + 1));
        val.resize(n);
    }
    void elimination(){
        for(int i = 0; i < n; i++){
            if(m[i][i] == 0){
                for(int j = i + 1; j < n; j++){
                    if(m[j][i]){
                        swap(m[i], m[j]);
                        break;
                    }
                }
            }
            for(int j = i + 1; j < n; j++){
                int t = m[j][i] * mypow(m[i][i], mod - 2) % mod;
                for(int k = i; k < n + 1; k++){
                    m[j][k] -= t * m[i][k] % mod;
                }
            }
        }
        val[n - 1] = m[n - 1][n] * mypow(m[n - 1][n - 1], mod - 2) % mod;
        for(int i = n - 2; ~i; --i){
            val[i] = m[i][n];
            for(int j = n - 1; j > i; --j){
                val[i] -= val[j] * m[i][j] % mod;
            }
            val[i] = val[i] * mypow(m[i][i], mod - 2) % mod;
        }
        reverse(all(val));
    }
    void print(){
        for(int i : val)cout << (i + mod) % mod << ' ';
    }
};
