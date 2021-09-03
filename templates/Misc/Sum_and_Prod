int sum(int a, int b){
    while(b){
        int carry = a & b;
        a ^= b;
        b = carry << 1;
    }
    return a;
}

int prod(int a, int b){
    int c = 0;
    for(; b; b >>= 1, a <<= 1){
        if(b & 1)c = sum(c, a);
    }
    return c;
}
