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

string solve(){
    int x[4], y[4];
    for(int i = 0; i < 4; i++)cin >> x[i] >> y[i];
    segment a({x[0], y[0]}, {x[1], y[1]}), b({x[2], y[2]}, {x[3], y[3]});
    if(a.twosided(b) && b.twosided(a))return "YES\n";
    if(a.onsegment(b.ends[0]) || a.onsegment(b.ends[1]) || b.onsegment(a.ends[0]) || b.onsegment(a.ends[1]))return "YES\n";
    return "NO\n";
}
