/// returns (a^b) % m
ll bigMod(ll a,ll b,ll m){
    ll ret = 1LL;
    a %= m;
    while (b){
        if (b & 1LL) ret = (ret * a) % m;
        a = (a * a) % m;
        b >>= 1LL;
    }
    return ret;
}


/// returns (x,y) of the equation ax + by = gcd(a,b)
PLL extEuclid(ll a,ll b) {
    if(b==0LL) return make_pair(1LL,0LL);
    PLL ret,got;
    got = extEuclid(b,a%b);
    ret = make_pair(got.yy,got.xx-(a/b)*got.yy);
    return ret;
}

/// returns modular invers of a with respect to m
/// inverse exists if and only if a and m are co-prime
ll modularInverse(ll a, ll m){
    ll x, y, inv;
    PLL sol = extEuclid(a,m);
    inv = (sol.xx + m) % m;
    return inv;
}
