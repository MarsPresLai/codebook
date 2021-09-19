template<class T> struct BIT{
    vector<T> rt;
    int sz;
    void init(int n){sz = n; rt.resize(sz);}
    void add(int i, T v){
        for(; i < sz; i += i & -i)rt[i] += v;
    }
    T sum(int i){
        int ans = 0;
        for(; i; i ^= i & -i)ans += rt[i];
        return ans;
    }
};

template<class T> struct range_BIT{
    BIT<T> a, b;
    int sz;
    range_BIT(int n) : sz(n + 1){a.init(sz), b.init(sz);}
    void add(int l, int r, T v){
        a.add(l, v);
        a.add(r + 1, -v);
        b.add(l, v * (l - 1));
        b.add(r + 1, -v * r);
    }
    T sum(int i){return i * a.sum(i) - b.sum(i);}
    T range_sum(int l, int r){return sum(r) - sum(l - 1);}
};
