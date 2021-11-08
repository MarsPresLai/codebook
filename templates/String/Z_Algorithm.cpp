string s;
cin >> s;
int n = s.size();
vector<int> z(n);
int l = 0, r = 0;
for(int i = 0; i < n; i++){
    z[i] = max(min(z[i - l], r - i), 0ll);
    while(z[i] < n && s[i + z[i]] == s[z[i]]){
        l = i, r = i + z[i]++;
    }
}
