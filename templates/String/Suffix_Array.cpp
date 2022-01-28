string s;
s += '$';
int n = s.size();
vector<int> sa(n), rk(n);
iota(all(sa), 0);
sort(all(sa), [&](int i, int j){
    return s[i] < s[j];
});
rk[sa[0]] = 0;
for(int i = 1; i < n; i++){
    rk[sa[i]] = rk[sa[i - 1]] + (s[sa[i]] != s[sa[i - 1]]);
}
for(int k = 0; (1 << k) < n; k++){
    vector<pair<int, int>> cmp;
    for(int i = 0; i < n; i++)cmp.push_back({rk[i], rk[(i + (1 << k)) % n]});
    sort(all(sa), [&](int i, int j){
        return cmp[i] < cmp[j];
    });
    rk[sa[0]] = 0;
    for(int i = 1; i < n; i++)rk[sa[i]] = rk[sa[i - 1]] + (cmp[sa[i - 1]] != cmp[sa[i]]);
}
vector<int> lcp(n);
int val = 0;
for(int i = 0; i < n; i++){
    if(rk[i] == 0)continue;
    if(val)--val;
    int pre = sa[rk[i] - 1];
    while(i + val < n && pre + val < n && s[i + val] == s[pre + val])val++;
    lcp[rk[i]] = val;
}
