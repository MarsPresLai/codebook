#define double long double
#define pt complex<double>
#define X real()
#define Y imag()

double dot(pt a, pt b){return (conj(a) * b).X;}
double cross(pt a, pt b){return (conj(a) * b).Y;}
double turn(pt x, pt a, pt b){return cross(x - a, b - a);}
bool online(pt x, pt a, pt b){
    if(dot(a - x, b - x) <= 0 && abs(turn(x, a, b)) <= 1e-6)return true;
    return false;
}
bool intersect(pt a1, pt a2, pt b1, pt b2){
    if(online(a1, b1, b2) || online(a2, b1, b2) || online(b1, a1, a2) || online(b2, a1, a2))return true;
    if(turn(a1, b1, b2) * turn(a2, b1, b2) < 0 && turn(b1, a1, a2) * turn(b2, a1, a2) < 0)return true;
    return false;
}

pt proj(pt x, pt a, pt b){
    pt dir = b - a;
    double c = dir.Y * a.X - dir.X * a.Y, t = (dir.Y * x.X - dir.X * x.Y - c) / (dir.X * dir.X + dir.Y * dir.Y);
    return {x.X - dir.Y * t, x.Y + dir.X * t};
}

double ptline(pt x, pt a, pt b){
    if(a == b)return abs(x - a);
    pt pro = proj(x, a, b);
    if(online(pro, a, b)){
        return abs(pro - x);
    }
    return min(abs(x - a), abs(x - b));
}
