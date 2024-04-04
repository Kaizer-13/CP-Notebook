const int MOD = 1000000007;
int inv[MAX],fact[MAX];

void precal(int N) {
    fact[0] = 1;
    for(int i=1;i<=N;i++)  fact[i] = ( (long long)fact[i-1]*i )  % MOD;
    inv[N] = bigMod(fact[N],MOD-2,MOD);
    for (int i = N - 1 ; i >= 0; i--)
        inv[i] = ( (long long)inv[i + 1]*(i + 1) ) % MOD;
}

/// returns nCr
int bin(int n,int r) {
    if(n<r) return 0;
    ll ret = fact[n];
    ret *= inv[r] , ret %= MOD;
    ret *= inv[n-r] , ret %= MOD;
    return ret;
}
