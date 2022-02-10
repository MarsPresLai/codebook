struct node{
    int val = 0;
    node *lc, *rc, *p;
    node(){lc = rc = p = NULL;}
    bool lr(){return p && p -> lc = this;}// true l false r
    void rotate_left(){
        node *tmp = lc;
        p -> p = this;
        lc = p;
        p -> rc = tmp;
        if(tmp)tmp -> p = p;
    }
    void rotate_right(){
        node *tmp = rc;
        p -> p = this;
        rc = p;
        p -> lc = tmp;
        if(tmp)tmp -> p = p;
    }
    void rotate(){lr() ? rotate_right() : rotate_left();}
    void splay(node *top = NULL){
        node *rt = this;
        while(rt -> p != top){
            if(rt -> p -> p != top)
                (lr() ^ p -> lr() ? p : this) -> rotate();
            rotate();
        }
    }
    void insert(node *x){
        
    }
};
