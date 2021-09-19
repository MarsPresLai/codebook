template<class T> struct seg{
    T val, lz;
    seg<T> *lc, *rc;
    int sz;
    seg(int n) : sz(n){val = lz = 0; lc = rc = NULL;}
    void pull(){
        val = (lc ? lc -> val : 0) + (rc ? rc -> val : 0);
    }
    void push(int l, int r){
        int m = l + r >> 1;
        if(!lc)lc = new seg(m - l);
        if(!rc)rc = new seg(r - m);
        if(!lz)return;
        lc -> val = lc -> sz;
        lc -> lz = 1;
        rc -> val = rc -> sz;
        rc -> lz = 1;
        lz = 0;
    }
    void add(int a, int b, T v, int l, int r){
        if(a <= l && b >= r){
            val = r - l, lz = 1;
            return;
        }
        push(l, r);
        int m = l + r >> 1;
        if(a < m){
            lc -> add(a, b, v, l, m);
        }
        if(b > m){
            rc -> add(a, b, v, m, r);
        }
        pull();
    }
    T query(int a, int b, int l, int r){
        if(a <= l && b >= r)return val;
        push(l, r);
        int m = l + r >> 1, ans = 0;
        if(a < m)ans += lc -> query(a, b, l, m);
        if(b > m)ans += rc -> query(a, b, m, r);
        return ans;
    }
    void add(int a, int b, T v){add(a, b, v, 0, sz);}
    T query(int a, int b){return query(a, b, 0, sz);}
};
