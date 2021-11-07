int dis(int x1, int y1, int x2, int y2){
    return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
}

signed main(){
    setIO();
    int n;
    cin >> n;
    vector<pair<int, int>> a(n);
    for(auto &i : a)cin >> i;
    sort(all(a), [&](auto i, auto j){
        return i.second < j.second;
    });
    int ans = INF, ptr = 0;
    set<pair<int, int>> pt;
    for(int i = 0; i < n; i++){
        while(ptr < i && a[ptr].second < a[i].second - sqrtl(ans) - 1)pt.erase(a[ptr++]);
        auto it = pt.lower_bound(make_pair(a[i].first - sqrtl(ans) - 1, 0));
        for(; it != pt.end(); it++){
            if(it -> first > a[i].first + sqrtl(ans) + 1)break;
            ans = min(ans, dis(it -> first, it -> second, a[i].first, a[i].second));
        }
        pt.insert(a[i]);
    }
    cout << ans;
}
