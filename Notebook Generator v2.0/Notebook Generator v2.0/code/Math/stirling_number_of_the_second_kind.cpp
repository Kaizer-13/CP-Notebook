// 1 / k! * sum (-1)^i nCr(k, i) * (k - i) ^ n 
ll f(int n, int k) {
    ll res = 0;
    for (int i = 0; i < k; ++i) {
        if (i & 1) res = (res - nCr(k, i) * bp(k - i, n, mod) % mod + mod) % mod;
        else res = (res + nCr(k, i) * bp(k - i, n, mod) % mod) % mod;
    }
    if (res < 0) res += mod;
    return res * ifac[k] % mod;
}
