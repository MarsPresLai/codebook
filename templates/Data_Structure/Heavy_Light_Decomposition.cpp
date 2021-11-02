vector<int> adj[N];
int sz[N], h[N]{}, dep[N]{}, in[N], pa[N], now = 0;
 
void dfs(int i = 0, int p = -1){
    pa[i] = p;
    sz[i] = 1;
    for(int &j : adj[i])if(j != p){
        dep[j] = dep[i] + 1;
        dfs(j, i);
        sz[i] += sz[j];
        if(sz[j] > sz[adj[i][0]])swap(j, adj[i][0]);
    }
}
 
void hld(int i = 0, int p = -1){
    in[i] = now++;
    for(int j : adj[i])if(j != p){
        h[j] = (j == adj[i][0] ? h[i] : j);
        hld(j, i);
    }
}
 
void upd(int i, int v){
    change(in[i], v);
}
 
int qry(int i, int j){
    int ans = 0;
    for(; h[j] != h[i]; j = pa[h[j]]){
        if(dep[h[i]] > dep[h[j]])swap(i, j);
        ans = max(ans, query(in[h[j]], in[j] + 1));
    }
    if(dep[i] > dep[j])swap(i, j);
    ans = max(ans, query(in[i], in[j] + 1));
    return ans;
}
