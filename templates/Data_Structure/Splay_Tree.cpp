struct node{
    int val, sz;
    node *lc, *rc, *pa;
    node(){val = sz = 0; lc = rc = pa = NULL;}
    node(int i){val = i; sz = 1; lc = rc = pa = NULL;}
    bool isLeft(){return pa && pa -> lc == this;}
    bool isRight(){return pa && pa -> rc == this;}
    node *&ch(bool b){return b ? lc : rc;}
    void rotate(bool b){
        node *x = ch(b);
        if(isLeft())pa -> lc = x;
        else if(isRight())pa -> rc = x;
        x -> pa = pa;
        ch(b) = x -> ch(!b);
        if(x -> ch(!b))x -> ch(!b) -> pa = this;
        x -> ch(!b) = this;
        pa = x;
        x -> sz = sz;
        sz = get_sz(lc) + get_sz(rc) + 1;
    }
    void rotateTop(){pa -> rotate(isLeft());}
    void splay(node *top = NULL){
        while(pa != top){
            if(pa -> pa != top)(isLeft() ^ pa -> isLeft() ? this : pa) -> rotateTop();
            rotateTop();
        }
    }
    node *find_last(){
        return rc ? rc -> find_last() : this;
    }
    friend void merge(node *a, node *b){
        if(!a || !b)return;
        a -> splay();
        node *x = a -> find_last();
        x -> splay();
        b -> splay();
        x -> rc = b;
        b -> pa = x;
        x -> sz += b -> sz;
    }
    void insert(node *a){
        splay();
        if(!lc)lc = a, a -> pa = this, sz++;
        else{
            lc -> find_last() -> splay(this);
            lc -> rc = a, a -> pa = lc;
            sz++, lc -> sz++;
        }
    }
    void erase(){
        splay();
        if(lc)lc -> pa = NULL;
        if(rc)rc -> pa = NULL;
        merge(lc, rc);
        lc = rc = NULL;
    }
    int get_sz(node *&a){return a ? a -> sz : 0;}
    node *kth(int k){
        if(get_sz(lc) >= k)return lc -> kth(k);
        if(k == get_sz(lc) + 1)return this;
        return rc -> kth(k - get_sz(lc) - 1);
    }
    void insert(int k, int v){
        splay();
        kth(k) -> insert(new node(v));
    }
    void erase(int k){
        kth(k) -> erase();
    }
    void print(int k){
        splay();
        cout << kth(k) -> val << '\n';
    }
};
