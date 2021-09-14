void count_sort(vector<int> &p, vector<int> &c){
    int n = p.size();
    vector<int> cnt(n), pos(n), new_p(n);
    for(int i : c)cnt[i]++;
    for(int i = 1; i < n; i++){
        pos[i] = pos[i - 1] + cnt[i - 1];
    }
    for(int i = 0; i < n; i++){
        new_p[pos[c[p[i]]]++] = p[i];
    }
    p = new_p;
}

signed main(){
    string s;
    cin >> s;
    s += '$';
    int n = s.size();
    vector<int> p(n), c(n);
    {
        vector<int> cnt(128), pos(128);
        for(char c : s)cnt[c]++;
        pos[0] = 0;
        for(int i = 1; i < 128; i++){
            pos[i] = pos[i - 1] + cnt[i - 1];
        }
        for(int i = 0; i < n; i++){
            p[pos[s[i]]++] = i;
        }
        c[p[0]] = 0;
        for(int i = 1; i < n; i++){
            c[p[i]] = c[p[i - 1]];
            if(s[p[i]] != s[p[i - 1]])c[p[i]]++;
        }
    }
    {
        int k = 0;
        while((1 << k) < n){
            for(int i = 0; i < n; i++){
                p[i] = (p[i] - (1 << k) + n) % n;
            }
            count_sort(p, c);
            vector<int> new_c(n);
            new_c[p[0]] = 0;
            for(int i = 1; i < n; i++){
                pair<int, int> now = {c[p[i]], c[(p[i] + (1 << k)) % n]}, pre = {c[p[i - 1]], c[(p[i - 1] + (1 << k)) % n]};
                new_c[p[i]] = new_c[p[i - 1]];
                if(now != pre)new_c[p[i]]++;
            }
            c = new_c;
            k++;
        }
    }
    for(int i : p)cout << i << ' ';
}
