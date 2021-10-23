#define double long double
#define pt complex<double>
#define X real()
#define Y imag()

double dot(pt a, pt b){return (conj(a) * b).X;}
double cross(pt a, pt b){return (conj(a) * b).Y;}
double turn(pt x, pt a, pt b){return cross(b - a, x - a);}

vector<pt> convexhull(vector<pt> &point){
    int n = point.size();
    auto start = *min_element(all(point), [&](pt x, pt y){
        if(x.X != y.X)return x.X < y.X;
        return x.Y < y.Y;
    });
    vector<pt> st(1, start);
    sort(all(point), [&](pt x, pt y){
        pt dx = x - start, dy = y - start;
        double c = cross(dx, dy);
        return c ? c > 0 : abs(x - start) < abs(y - start);
    });
    for(auto i : point){
        if(i == start)continue;
        while(st.size() > 1 && turn(i, st[st.size() - 2], st.back()) <= 0)st.pop_back();
        st.push_back(i);
    }
    return st;
}
