struct BIT{
    vector<int> rt;
    int sz;
    BIT(int n){
        rt.resize(n + 1);
        sz = n + 1;
    }
	void add(int i, int v){
		for(; i < sz; i += i & -i)
			rt[i] += v;
	}
	int sum(int i){
		int ans  = 0;
		for(; i; i -= i & -i)
			ans += rt[i];
		return ans;
	}
};
