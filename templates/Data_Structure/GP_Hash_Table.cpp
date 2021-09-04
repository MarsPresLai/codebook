mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const int RNG = rng();
struct custom_hash{
    int operator ()(int x)const{
        return RNG ^ x;
    }
};

gp_hash_table<int, pair<int, int>, custom_hash> ht;
