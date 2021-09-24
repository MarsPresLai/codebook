int exgcd(int a, int b, int &x, int &y){
    if(!b){
        x = 1, y = 0;
        return a;
    }
    int xx, yy, g = exgcd(b, a % b, xx, yy);
    x = yy, y = xx - yy * (a / b);
    return g;
}
