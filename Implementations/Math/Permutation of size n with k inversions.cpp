/***
    Problem: https://www.hackerrank.com/contests/101hack43/challenges/k-inversion-permutations/problem

    Suppose, we have a permutation of size x with y inversions.
    We can get a new permutation of size (x+1) from that by
    inserting (x+1) somewhere in the previous permutation. The new
    permutation will have (y+y) inversions where (z <= x).

    Thus, every permutation of size n can having k inversions has one
    to one mapping to the solutions of the following equation.

    x_1 + x_2 + ... + x_n = k,  0 <= x_i <= (i-1)

    This equation can be solved by the help of inclusion exclusion.

    e_i --> (x_i >= i)

    ans = 0;
    for(s = 0; s <= k ; s++)
        ans += C(n+k-1-s, n-1) * F(s)

    F[s] = 0
    for(c = 0;; c++)
        F[s] += (-1)^c * G(s, c)

    **********************************************************************
    *   G(s, c) = number of ways to sum up to s using exactly c distinct *
    *             integers of range [1,n]                                *
    *           = G(s-c,c) + call(s-c,c-1) - call(s-(n+1),c-1)           *
    **********************************************************************

    As, the value of c can be approximately sqrt(k), the complexity
    of the whole solution is --> O(k * sqrt(k))
***/

#include <bits/stdc++.h>
using namespace std;
#define SET(a) memset(a,-1,sizeof(a))
const int MAX = 200010;
const int MOD = 1000000007;

int N;
int G[MAX][450];
inline int call(int i,int j) {
    if(i<0 or j<0) return 0;
    if(i==0) return (j==0);
    if(j==0) return (i==0);
    if(G[i][j]!=-1) return G[i][j];
    int ret = 0;
    ret = ( call(i-j,j) + call(i-j,j-1) ) % MOD;
    ret += (MOD - call(i-(N+1),j-1));
    if(ret>=MOD) ret -= MOD;
    return G[i][j] = ret;
}

int fact[MAX], inv[MAX], F[MAX];

void pre() {
    fact[0] = 1;
    inv[200000] = 750007460;
    for(int i=1;i<=2e5;i++) fact[i] = ( fact[i-1] * 1LL * i ) % MOD;
    for(int i=(2e5)-1;i>=0;i--) inv[i] = (inv[i+1] * 1LL * (i+1)) % MOD;
}

inline int C(int n,int r) {
    if(n<r) return 0;
    int ret = fact[n];
    ret = (ret * 1LL * inv[r]) % MOD;
    ret = (ret * 1LL * inv[n-r]) % MOD;
    return ret;
}

int main() {
//    freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);

    pre(); SET(G);
    int n,k;
    cin >> n >> k;
    N = n;

    for(int s=1;s<=k;s++) {
        for(int e=1;;e++) {
            if( (e * (e+1)) > s+s ) break;
            if(e & 1) {
                F[s] += (MOD - call(s,e));
                if(F[s]>=MOD) F[s] -= MOD;
            }
            else F[s] = (F[s] + call(s,e)) % MOD;
        }
    }
    int ans = C(n+k-1,n-1);
    for(int i=1;i<=k;i++) {
        ans += (F[i] * 1LL * C(n+k-1-i,n-1)) % MOD;
        ans %= MOD;
    }
    cout << ans << endl;
    return 0;
}
