vector<int> adj[N], rev[N], st;
int comp[N], vis[N];

void dfs(int i, int pass, int id = 0){
    vis[i] = 1;
    auto &g = (pass ? rev[i] : adj[i]);
    for(int j : g)if(!vis[j]){
        dfs(j, pass, id);
    }
    st.push_back(i);
    if(pass == 1)comp[i] = id;
}
