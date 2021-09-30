struct Dinic{
    struct edge{
        int to, flow, idx;
        edge(int _to, int _flow, int _idx) : to(_to), flow(_flow), idx(_idx){}
    };
    int n, s, t;
    vector<vector<edge>> adj;
    vector<int> level;
    Dinic(int _n, int _s, int _t) : n(_n), s(_s), t(_t){
        adj.resize(n);
        level.resize(n);
    }
    void add_edge(int u, int v, int cap){
        adj[u].push_back(edge(v, cap, adj[v].size()));
        adj[v].push_back(edge(u, 0, adj[u].size() - 1));
    }
    bool bfs(){
        queue<int> q;
        q.push(s);
        level.assign(n, -1);
        level[s] = 0;
        while(!q.empty()){
            int now = q.front(); q.pop();
            for(auto j : adj[now])if(j.flow && level[j.to] == -1){
                level[j.to] = level[now] + 1;
                q.push(j.to);
            }
        }
        return level[t] != -1;
    }
    int dfs(int i, int mnflow){
        if(i == t)return mnflow;
        int ans = 0;
        for(auto &j : adj[i])if(j.flow && level[j.to] == level[i] + 1){
            int nxtflow = dfs(j.to, min(mnflow, j.flow));
            j.flow -= nxtflow;
            ans += nxtflow;
            mnflow -= nxtflow;
            adj[j.to][j.idx].flow += nxtflow;
            if(!mnflow)return ans;
        }
        if(ans == 0)level[i] = -1;
        return ans;
    }
    int run_flow(){
        int ans = 0;
        while(bfs()){
            ans += dfs(s, INF);
        }
        return ans;
    }
};
