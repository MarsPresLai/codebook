// splay
struct node{
    node *lc, *rc, *pa;
    int sz, rev;
    node(){lc = rc = pa = NULL; sz = 1; rev = 0;}
    bool L(){return pa && pa -> lc == this ? 1 : 0;}
    bool R(){return pa && pa -> rc == this ? 1 : 0;}
    bool RT(){return !L() && !R();}
    void push(){
        if(rev){
            if(lc)lc -> rev ^= rev;
            if(rc)rc -> rev ^= rev;
            swap(lc, rc);
            rev = 0;
        }
    }
    node *&ch(bool d){return d ? lc : rc;}
    void rotate(bool d){
        node *x = ch(d);
        if(!RT())pa -> ch(L()) = x;
        x -> pa = pa;
        ch(d) = x -> ch(!d);
        if(x -> ch(!d))x -> ch(!d) -> pa = this;
        x -> ch(!d) = this;
        pa = x;
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
        node *now = &rt[v], *lst = NULL;
        for(node *x = now; x; x = x -> pa){
            x -> splay();
            x -> rc = lst;
            lst = x;
        }
        now -> splay();
    }
    void makert(int v){
        access(v);
        rt[v].rev ^= 1;
    }
    void link(int u, int v){
        makert(u);
        rt[u].pa = &rt[v];
    }
    void cut(int u, int v){
        makert(u);
        access(v);
        if(rt[v].lc){
            rt[v].lc = rt[v].lc -> pa = NULL;
        }
    }
    bool con(int u, int v){
        access(u);
        access(v);
        return rt[u].pa;
    }
};
