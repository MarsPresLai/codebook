struct node{
    node *lc, *rc, *pa;
    int val, sum;
    bool rev;
    node(){lc = rc = pa = NULL; val = sum = rev = 0;}
    bool L(){return pa && pa -> lc == this;}
    bool R(){return pa && pa -> rc == this;}
    bool RT(){return !L() && !R();}
    node *&ch(bool d){return d ? lc : rc;}
    int gets(node *x){return x ? x -> sum : 0;}
    void pull(){sum = gets(lc) + gets(rc) + val;}
    void push(){
        if(rev){
            if(lc)lc -> rev ^= 1;
            if(rc)rc -> rev ^= 1;
            swap(lc, rc);
            rev = 0;
        }
    }
    void rotate(bool d){
        node *x = ch(d);
        if(!RT())pa -> ch(L()) = x;
        x -> pa = pa;
        ch(d) = x -> ch(!d);
        if(x -> ch(!d))x -> ch(!d) -> pa = this;
        x -> ch(!d) = this;
        pa = x;
        pull();
        x -> pull();
    }
    void rotateTop(){pa -> rotate(L());}
    void pushall(){if(!RT())pa -> pushall(); push();}
    void splay(){
        pushall();
        while(!RT()){
            if(!pa -> RT())(L() ^ pa -> L() ? this : pa) -> rotateTop();
            rotateTop();
        }
    }
};

struct LCT{
    vector<node> rt;
    LCT(int n){rt.resize(n);}
    void access(int v){
        node *x = &rt[v], *lst = NULL;
        for(node *now = x; now; now = now -> pa){
            now -> splay();
            now -> rc = lst;
            now -> pull();
            lst = now;
        }
        x -> splay();
    }
    void makert(int v){
        access(v);
        rt[v].rev ^= 1;
    }
    void link(int u, int v){
        makert(u);
        rt[u].pa = &rt[v];
        rt[v].pull();
    }
    void cut(int u, int v){
        makert(u);
        access(v);
        if(rt[v].lc)rt[v].lc = rt[v].lc -> pa = NULL;
        rt[v].pull();
    }
    void add(int v, int i){
        access(v);
        rt[v].val += i;
        rt[v].pull();
    }
    int sum(int u, int v){
        makert(u);
        access(v);
        return rt[v].sum;
    }
};
