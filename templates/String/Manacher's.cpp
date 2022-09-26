string s;
int n = s.size();
vector<int> z(n);
int l = 1, r = 1;
for(int i = 1; i < n; i++){
  z[i] = max(min(z[l + (r - i)], r - i), 0);
  while(i + z[i] < n && i - z[i] >= 0 && s[i + z[i]] == s[i - z[i]]){
    z[i]++;
  }
  if(i + z[i] > r)r = i + z[i], l = i - z[i];
}
