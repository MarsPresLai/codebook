const int INF = 2e18, N = 3e5 + 2;

struct undoable_DSU{
    vector<int> f;
    vector<pair<int, int>> undosz, undopa;
    int cc, sz;
    void init(int n){sz = cc = n, f.resize(n, -1);}
    int Find(int i){return f[i] < 0 ? i : Find(f[i]);}
    bool Union(int i, int j){
        i = Find(i), j = Find(j);
        if(i == j){
            undosz.push_back({INF, INF});
            undopa.push_back({INF, INF});
            return false;
        }
        cc--;
        if(f[i] > f[j])swap(i, j);
        undosz.push_back({i, f[i]});
        undopa.push_back({j, f[j]});
        f[i] += f[j];
        f[j] = i;
        return true;
    }
    void undo(){
        auto i = undosz.back(), j = undopa.back();
        undosz.pop_back();
        undopa.pop_back();
        if(i == make_pair(INF, INF) && j == make_pair(INF, INF))return;
        f[i.first] = i.second;
        f[j.first] = j.second;
        cc++;
    }
    int comp(){return cc;}
}dsu;

struct event{
    int u, v, l, r, idx = -1;
    bool operator <(const event &o)const{
        return l <= o.l;
    }
};

#define lc (p << 1)
#define rc (p << 1 | 1)

vector<event> seg[4 * N];
vector<int> ans;

void add(event v, int p = 1, int l = 0, int r = N){
    if(v.l <= l && v.r >= r)return void(seg[p].push_back(v));
    int m = l + r >> 1;
    if(v.l < m)add(v, lc, l, m);
    if(v.r > m)add(v, rc, m, r);
}

void run(int p = 1, int l = 0, int r = N){
    int cnt = 0;
    for(auto &e : seg[p]){
        if(e.idx == -1){
            cnt++;
            dsu.Union(e.u, e.v);
        }else{
            ans[e.idx] = dsu.comp();
        }
    }
    if(r - l == 1){
        while(cnt--)dsu.undo();
        return;
    }
    int m = l + r >> 1;
    run(lc, l, m);
    run(rc, m, r);
    while(cnt--)dsu.undo();
}

signed main(){
    setIO();
    int n, q;
    cin >> n >> q;
    dsu.init(n);
    map<pair<int, int>, pair<int, int>> s;// {u, v} {idx, cnt}
    vector<event> E;
    int qry = 0;
    for(int i = 0; i < q; i++){
        char c;
        cin >> c;
        if(c == '?'){
            E.push_back({0, 0, i, i + 1, qry++});
        }else{
            int u, v;
            cin >> u >> v;
            if(v > u)swap(u, v);
            --u, --v;
            pair<int, int> now = {u, v};
            if(c == '+'){
                if(s[now].second)s[now].second++;
                else s[now] = {i, 1};
            }else{
                s[now].second--;
                if(s[now].second == 0){
                    E.push_back({u, v, s[now].first, i + 1, -1});
                }
            }
        }
    }
    for(auto &i : s){
        if(i.second.second){
            E.push_back({i.first.first, i.first.second, i.second.first, q + 1, -1});
        }
    }
    sort(all(E));
    for(auto &i : E){
        add(i);
    }
    ans.resize(qry);
    run();
    for(int i : ans)cout << i << '\n';
}
