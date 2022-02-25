#define C complex<double>
 
const double pi = acos(-1);
 
void FFT(vector<C> &a, int inv = 1){
    int n = a.size();
    for(int i = 1, j = 0; i < n; i++){
        int bit = n >> 1;
        for(; bit & j; bit >>= 1)
            j ^= bit;
        j ^= bit;
        if(i < j)swap(a[i], a[j]);
    }
    for(int len = 2; len <= n; len <<= 1){
        double ang = 2 * pi / len * inv;
        C rot(cos(ang), sin(ang));
        for(int i = 0; i < n; i += len){
            C w(1);
            for(int j = 0; j < len / 2; j++){
                C u = a[i + j], v = w * a[i + j + len / 2];
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                if(inv == -1)a[i + j] /= 2, a[i + j + len / 2] /= 2;
                w *= rot;
            }
        }
    }
}
 
void mul(vector<C> &a, vector<C> &b){
    int n = a.size() + b.size() - 1;
    int len = 1 << __lg(n) + 1;
    a.resize(len);
    b.resize(len);
    FFT(a), FFT(b);
    for(int i = 0; i < len; i++)a[i] *= b[i];
    FFT(a, -1);
    a.resize(n);
}
