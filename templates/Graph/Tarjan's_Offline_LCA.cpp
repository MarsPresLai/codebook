vector<int> adj[N];
vector<pair<int, int>> qry[N];
int vis[N]{}, anc[N], ans[N]{};
DSU dsu;

void tarjan_lca(int i = 0, int p = 0){
    vis[i] = 1;
    anc[i] = i;
    for(int j : adj[i])if(j != p){
        dfs(j, i);
        dsu.Union(i, j);
        anc[dsu.Find(i)] = i;
    }
    for(auto [j, idx] : qry[i]){
        if(vis[j]){
            ans[idx] = anc[dsu.Find(j)];
        }
    }
}
