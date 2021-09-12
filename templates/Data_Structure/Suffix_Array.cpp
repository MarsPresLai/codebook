    string s;
    cin >> s;
    s += '$';
    int n = s.size(), idx[n]{}, val[n]{};
    vector<pair<char, int>> a;
    for(int i = 0; i < n; i++){
        a.push_back({s[i], i});
    }
    sort(all(a));
    for(int i = 0; i < n; i++)idx[i] = a[i].second;
    val[idx[0]] = 0;
    for(int i = 1; i < n; i++){
        val[idx[i]] = val[idx[i - 1]];
        if(a[i].first != a[i - 1].first)val[idx[i]]++;
    }
    int k = 0;
    while((1 << k) < n){
        vector<pair<pair<int, int>, int>> cal(n);
        for(int i = 0; i < n; i++){
            cal[i] = {{val[i], val[(i + (1 << k)) % n]}, i};
        }
        sort(all(cal));
        for(int i = 0; i < n; i++)idx[i] = cal[i].second;
        val[idx[0]] = 0;
        for(int i = 1; i < n; i++){
            val[idx[i]] = val[idx[i - 1]];
            if(cal[i].first != cal[i - 1].first)val[idx[i]]++;
        }
        k++;
    }
    for(int i : idx)cout << i << ' ';
