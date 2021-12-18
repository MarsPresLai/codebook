const double pi = acos(-1);
#define cp complex<double>

void FFT(vector<cp> &a, int inv){
    int n = a.size();
    if(n == 1)return;
    vector<cp> ch[2];
    for(int i = 0; i < n; i++){
        ch[i & 1].push_back(a[i]);
    }
    FFT(ch[0], inv); FFT(ch[1], inv);
    double ang = 2 * pi / n * inv;
    cp w(1), rotate(cos(ang), sin(ang));
    for(int i = 0; i * 2 < n; i++){
        a[i] = ch[0][i] + w * ch[1][i];
        a[i + n / 2] = ch[0][i] - w * ch[1][i];
        if(inv == -1)a[i] /= 2, a[i + n / 2] /= 2;
        w *= rotate;
    }
}

signed main(){
    setIO();
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for(int &i : a)cin >> i;
    for(int &i : b)cin >> i;
    vector<cp> ca(all(a)), cb(all(b));
    int sz = 1;
    while(sz < n + m)sz <<= 1;
    ca.resize(sz), cb.resize(sz);
    FFT(ca, 1);
    FFT(cb, 1);
    for(int i = 0; i < sz; i++)ca[i] *= cb[i];
    FFT(ca, -1);
    for(int i = 0; i < n + m - 1; i++)cout << round(ca[i].real()) << ' ';
}
