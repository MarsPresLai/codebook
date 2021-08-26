struct BIT{
    vector<int> rt;
    int size;
    BIT(int n){
        rt.resize(n + 1);
        size = n + 1;
    }
	void add(int i, int v){
		for(; i < size; i += i & -i)
			rt[i] += v;
	}
	int sum(int i){
		int ans  = 0;
		for(; i; i -= i & -i)
			ans += rt[i];
		return ans;
	}
};
