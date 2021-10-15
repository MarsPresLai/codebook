#define lc (p << 1)
#define rc (p << 1 | 1)
template<class T> struct segtree{
    struct node{
        T val, lz;
        node(){val = lz = 0;}
        void push(T v){
            val += v;
            lz += v;
        }
    };
    int sz;
    vector<node> seg;
    segtree(int n) : sz(n){seg.resize(4 * sz);}
    void pull(int p){seg[p].val = min(seg[lc].val, seg[rc].val);}
    void push(int p){
        if(seg[p].lz){
            seg[lc].push(seg[p].lz);
            seg[rc].push(seg[p].lz);
            seg[p].lz = 0;
        }
    }
    void add(int a, int b, T v, int p, int l, int r){
        if(a <= l && b >= r)return void(seg[p].push(v));
        push(p);
        int m = l + r >> 1;
        if(a < m)add(a, b, v, lc, l, m);
        if(b > m)add(a, b, v, rc, m, r);
        pull(p);
    }
    T query(int a, int b, int p, int l, int r){
        if(a <= l && b >= r)return seg[p].val;
        push(p);
        int m = l + r >> 1;
        T ans = INF;
        if(a < m)ans = min(ans, query(a, b, lc, l, m));
        if(b > m)ans = min(ans, query(a, b, rc, m, r));
        return ans;
    }
    void add(int a, int b, T v){add(a, b, v, 1, 0, sz);}
    T query(int a, int b){return query(a, b, 1, 0, sz);}
};
