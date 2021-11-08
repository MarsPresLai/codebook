string s, t;
int n = s.size(), m = t.size();
vector<int> fail(n + 1);
int k = -1;
fail[0] = -1;
for(int i = 1; i < n; i++){
    while(k != -1 && s[i] != s[k + 1])k = fail[k];
    if(s[i] == s[k + 1])k++;
    fail[i] = k;
}
k = -1;
for(int i = 0; i < m; i++){
    while(k != -1 && t[i] != s[k + 1])k = fail[k];
    if(t[i] == s[k + 1])k++;
    if(k + 1 == n){
        cout << i - k << ' ';
        k = fail[k];
    }
}
