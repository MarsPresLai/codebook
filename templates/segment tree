vector<int> a;
struct seg{
    int l, r, m, val = 0, lazy = 0;
    seg* child[2];
    seg(int i, int j) : l(i), r(j), m(l + r >> 1){
        if(r - l == 1){
            val = a[l];
        }else{
            child[0] = new seg(l, m);
            child[1] = new seg(m, r);
            pull();
        }
    }
    int size(){
        return r - l;
    }
    void pull(){
        val = child[0] -> val + child[1] -> val;
    }
    void push(){
        if(lazy && r - l != 1){
            child[0] -> lazy += lazy;
            child[1] -> lazy += lazy;
            child[0] -> val += lazy * child[0] -> size();
            child[1] -> val += lazy * child[1] -> size();
        }
        lazy = 0;
    }
    void set(int i, int v){
        if(r - l == 1){
            val = v;
        }else{
            if(i < m)child[0] -> set(i, v);
            else child[1] -> set(i, v);
            pull();
        }
    }
    int query(int i, int j){
        if(i <= l && j >= r){
            return val;
        }else{
            int ans = 0;
            push();
            if(i < m)ans += child[0] -> query(i, j);
            if(j > m)ans += child[1] -> query(i, j);
            return ans;
        }
    }
    void add(int a, int b, int v){
        if(a <= l && b >= r){
            lazy += v;
            val += v * size();
        }else{
            push();
            if(a < m)child[0] -> add(a, b, v);
            if(b > m)child[1] -> add(a, b, v);
            pull();
        }
    }
};
