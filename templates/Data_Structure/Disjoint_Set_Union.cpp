struct DSU{
    vector<int> rt;
    DSU(int n){rt.resize(n + 1, -1);}
    int Find(int i){return rt[i] < 0 ? i : rt[i] = Find(rt[i]);}
    void Union(int i, int j){
        int x = Find(i), y = Find(j);
        if(rt[x] > rt[y])swap(x, y);
        rt[x] += rt[y];
        rt[y] = x;
    }
    bool Same(int i, int j){return Find(i) == Find(j);}
};
