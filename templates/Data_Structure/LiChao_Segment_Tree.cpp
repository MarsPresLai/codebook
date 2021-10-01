#define lc (p << 1)
#define rc (p << 1 | 1)
 
struct line{
	int a, b;
	line(){a = 0, b = INF;}
	line(int aa, int bb) : a(aa), b(bb){}
	int eval(int x){
		return a * x + b;
	}
}seg[4 * N];
 
void add(line x, int p = 1, int l = 0, int r = N){
	int m = l + r >> 1;
	if(x.eval(m) < seg[p].eval(m))swap(seg[p], x);
	if(r - l == 1)return;
	if(x.eval(l) < seg[p].eval(l))add(x, lc, l, m);
	else add(x, rc, m, r);
}
 
int qry(int x, int p = 1, int l = 0, int r = N){
	int ans = seg[p].eval(x);
	if(r - l == 1)return ans;
	int m = l + r >> 1;
	if(x < m)return min(ans, qry(x, lc, l, m));
	else return min(ans, qry(x, rc, m, r));
}
