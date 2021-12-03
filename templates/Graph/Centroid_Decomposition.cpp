const int N = 2e5;
vector<int> adj[N], pa(N, -1);
int sz[N]{};

void get_size(int i, int p){
    sz[i] = 1;
    for(int j : adj[i])if(j != p && pa[j] == -1){
        get_size(j, i);
        sz[i] += sz[j];
    }
}

int get_centroid(int i, int p, int n){
    for(int j : adj[i])if(j != p){
        if(pa[j] == -1 && sz[j] >= n / 2)return get_centroid(j, i, n);
    }
    return i;
}

void centroid_decomposition(int i = 0, int p = -1){
    get_size(i, p);
    int c = get_centroid(i, p, sz[i]);
    pa[c] = ~p ? p : c;
    for(int j : adj[c])if(pa[j] == -1)centroid_decomposition(j, c);
}
