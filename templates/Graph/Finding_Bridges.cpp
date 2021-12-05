vector<int> adj[N];
int dep[N]{}, dp[N]{}, bridge = 0;
bool vis[N]{};

void dfs(int i, int p = -1){
    vis[i] = 1;
    for(int j : adj[i]){
        if(!vis[j]){
            dep[j] = dep[i] + 1;
            dfs(j, i);
            dp[i] += dp[j];
        }else if(dep[j] > dep[i]){
            dp[i]--;
        }else if(j != p){
            dp[i]++;
        }
    }
    if(i > 1 && dp[i] == 0)bridge++;
}

signed main(){
    setIO();
    int n, m;
    cin >> n >> m;
    while(m--){
        int u, v;
        cin >> u >> v;
        adj[u].push_back({v, 0});
        adj[v].push_back({u, 0});
    }
    dfs(1);
}

