const int N = 2e5, K = __lg(N) + 1;
int jump[N][K];

void build_lca(int i = 0, int p = 0){
    jump[i][0] = p;
    for(int k = 1; k < K; k++)
        jump[i][k] = jump[jump[i][k - 1]][k - 1];
    for(int j : adj[i])if(j != p)build_lca(j, i);
}

int lca(int i, int j){
    if(depth[i] > depth[j])swap(i, j);
    for(int k = K - 1; ~k; --k){
        if(depth[j] - (1 << k) >= depth[i])j = jump[j][k];
    }
    if(i == j)return i;
    for(int k = K - 1; ~k; --k){
        if(jump[i][k] != jump[j][k])
            i = jump[i][k], j = jump[j][k];
    }
    return jump[i][0];
}
