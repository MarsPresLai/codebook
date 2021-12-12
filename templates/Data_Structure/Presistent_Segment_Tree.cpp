struct node{
    node *lc, *rc;
    int val;
    node(){lc = rc = NULL; val = 0;}
};

int get(node *p){return p ? p -> val : 0;}
node *lc(node *p){return p ? p -> lc : NULL;}
node *rc(node *p){return p ? p -> rc : NULL;}
void pull(node *p){p -> val = get(p -> lc) + get(p -> rc);}

node *add(int i, node *p, int l = 0, int r = N){
    p = (p ? new node(*p) : new node());
    if(r - l == 1){
        p -> val++;
        return p;
    }
    int m = l + r >> 1;
    if(i < m)p -> lc = add(i, p -> lc, l, m);
    else p -> rc = add(i, p -> rc, m, r);
    pull(p);
    return p;
}

int kth(int k, node *a, node *b, int l = 0, int r = N){
    if(r - l == 1)return l;
    int m = l + r >> 1, val = get(lc(b)) - get(lc(a));
    if(val < k)return kth(k - val, rc(a), rc(b), m, r);
    else return kth(k, lc(a), lc(b), l, m);
}
