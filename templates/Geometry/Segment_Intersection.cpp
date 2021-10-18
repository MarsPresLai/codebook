#define pt complex<double>
#define X real()
#define Y imag()

struct segment{
    pt ends[2];
    pt dir;
    segment(pt x, pt y){
        ends[0] = x; ends[1] = y;
        dir = ends[1] - ends[0];
    }
    double cross(segment o){
        return (conj(dir) * (o.dir)).Y;
    }
    double dot(segment o){
        return (conj(dir) * (o.dir)).X;
    }
    double turn(pt a, pt b, pt c){
        return segment(c, a).cross(segment(b, a));
    }
    bool twosided(segment o){
        double a = turn(ends[0], ends[1], o.ends[0]);
        double b = turn(ends[0], ends[1], o.ends[1]);
        return a * b < 0;
    }
    bool onsegment(pt a){
        segment x(a, ends[0]);
        if(x.dot(segment(a, ends[1])) <= 0 && turn(a, ends[0], ends[1]) == 0)return true;
        return false;
    }
};

pair<double, double> cramers(int a1, int b1, int c1, int a2, int b2, int c2){
    double delta = a1 * b2 - a2 * b1, deltax = c1 * b2 - c2 * b1, deltay = a1 * c2 - a2 * c1;
    return {deltax / delta, deltay / delta};
}
struct cmp{
    bool operator ()(pt x, pt y)const{
        if(x.X != y.X)return x.X < y.X;
        return x.Y < y.Y;
    }
};

void solve(){
    int x[4], y[4];
    for(int i = 0; i < 4; i++)cin >> x[i] >> y[i];
    segment a({x[0], y[0]}, {x[1], y[1]}), b({x[2], y[2]}, {x[3], y[3]});
    if(a.twosided(b) && b.twosided(a)){
        auto ans = cramers(a.dir.X, -b.dir.X, b.ends[0].X - a.ends[0].X, a.dir.Y, -b.dir.Y, b.ends[0].Y - a.ends[0].Y);
        cout << a.ends[0].X + ans.first * a.dir.X << ' ' << b.ends[0].Y + ans.second * b.dir.Y << '\n';
        return;
    }
    set<pt, cmp> ans;
    if(a.onsegment(b.ends[0]))ans.insert(b.ends[0]);
    if(a.onsegment(b.ends[1]))ans.insert(b.ends[1]);
    if(b.onsegment(a.ends[0]))ans.insert(a.ends[0]);
    if(b.onsegment(a.ends[1]))ans.insert(a.ends[1]);
    if(ans.size() == 1){
        cout << (*ans.begin()).X << ' ' << (*ans.begin()).Y << '\n';
        return;
    }else if(ans.size() == 2){
        for(auto i : ans)cout << i.X << ' ' << i.Y << ' ';
        cout << '\n';
        return;
    }
    cout << "none\n";
    return;
}
