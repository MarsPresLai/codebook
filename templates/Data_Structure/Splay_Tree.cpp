struct node{
    node *lc, *rc, *pa;
    node(){lc = rc = pa = NULL;}
    bool isLeft(){return pa && pa -> lc == this;}
    bool isRight(){return pa && pa -> rc == this;}
    node*& ch(bool b){return b ? rc : lc;}
    void rotate(bool b){
        node *x = ch(b);
        if(isLeft())pa -> lc = x;
        else if(isRight())pa -> rc = x;
        x -> pa = pa;
        ch(b) = x -> ch(!b);
        if(x -> ch(!b))x -> ch(!b) -> pa = this;
        x -> ch(!b) = this;
        pa = x;
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
        a -> find_last() -> splay();
        b -> splay();
        a -> rc = b;
        b -> pa = a;
    }
    void insert(node *a){
        splay();
        if(!lc)lc = a, a -> pa = this;
        else{
            lc -> find_last() -> splay(this);
            lc -> rc = a, a -> pa = lc;
        }
    }
    void erase(){
        splay();
        if(lc)lc -> pa = NULL;
        if(rc)rc -> pa = NULL;
        merge(lc, rc);
        lc = rc = NULL;
    }
};
