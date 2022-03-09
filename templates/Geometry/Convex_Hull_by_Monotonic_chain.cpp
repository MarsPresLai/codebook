struct p{
    int x, y;
    p operator -(const p &o)const{
        return {x - o.x, y - o.y, 0};
    }
    int operator ^(const p &o)const{
        return x * o.y - y * o.x;
    }
};

signed main(){
    setIO();
    vector<p> a;
    sort(all(a), [&](p f, p s){
        if(f.x != s.x)return f.x < s.x;
        return f.y < s.y;
    });
    vector<p> upCH, downCH;
    for(int i = 0; i < (int)a.size(); i++){
        while(upCH.size() > 1 && ((a[i] - upCH.end()[-2]) ^ (upCH.end()[-1] - upCH.end()[-2])) < 0)upCH.pop_back();
        upCH.push_back(a[i]);
    }
    for(int i = 0; i < (int)a.size(); i++){
        while(downCH.size() > 1 && ((a[i] - downCH.end()[-2]) ^ (downCH.end()[-1] - downCH.end()[-2])) > 0)downCH.pop_back();
        downCH.push_back(a[i]);
    }
}
