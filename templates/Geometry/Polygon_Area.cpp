#define point complex<int>
#define X real()
#define Y imag()

signed main(){
    setIO();
    int n;
    cin >> n;
    vector<point> a(n);
    for(int i = 0; i < n; i++){
        int x, y;
        cin >> x >> y;
        a[i] = {x, y};
    }
    int ans = 0;
    a.push_back(a[0]);
    auto cross = [&](point x, point y){
        return (conj(x) * y).Y;
    };
    for(int i = 0; i < n; i++){
        ans += cross(a[i], a[i + 1]);
    }
    cout << abs(ans);
}
