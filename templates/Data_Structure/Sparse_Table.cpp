int n, q, k;
k = __lg(n) + 1;
int sparse[n][k];
for(int i = 0; i < n; i++)cin >> sparse[i][0];
for(int j = 1; j < k; j++){
    for(int i = 0; i + (1 << j) <= n; i++){
        sparse[i][j] = min(sparse[i][j - 1], sparse[i + (1 << j - 1)][j - 1]);
    }
}
auto level = [&](int i) -> int{
    return 31 - __builtin_clz(i);
};
while(q--){
    int a, b;
    cin >> a >> b;
    int l = level(b - a);
    cout << min(sparse[a][l], sparse[b - (1 << l)][l]) << '\n';
}
