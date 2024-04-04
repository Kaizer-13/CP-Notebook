Let A be the adjacency matrix of the graph: A[u][v] is the number of edges
between u and v.

Let D be the degree matrix of the graph: a diagonal matrix with D[u][u]
being the degree of vertex u (including multiple edges, ignore self loops).

The Laplacian matrix of the graph is defined as L = D − A.
M -> Submatrix of L discarding the last row and last column([n-1] * [n-1])

The number of different spanning tress of the graph = Determinant of M.


#include<bits/stdc++.h>
using namespace std;

#define mem(t, v)   memset ((t) , v, sizeof(t))
#define all(x)      x.begin(),x.end()
#define un(x)       x.erase(unique(all(x)), x.end())
#define sf(n)       scanf("%d", &n)
#define sff(a,b)    scanf("%d %d", &a, &b)
#define sfff(a,b,c) scanf("%d %d %d", &a, &b, &c)
#define sl(n)       scanf("%lld", &n)
#define sll(a,b)    scanf("%lld %lld", &a, &b)
#define slll(a,b,c) scanf("%lld %lld %lld", &a, &b, &c)
#define D(x)        cerr << __LINE__ << ": " << #x << " = " << (x) << '\n'
#define DD(x,y)     cerr << __LINE__ << ": " << #x << " = " << x << "   " << #y << " = " << y << '\n'
#define DDD(x,y,z)  cerr << __LINE__ << ": " << #x << " = " << x << "   " << #y << " = " << y << "   " << #z << " = " << z << '\n'
#define DBG         cerr << __LINE__ << ": Hi" << '\n'
#define pb          push_back
#define PI          acos(-1.00)
#define xx          first
#define yy          second
#define eps         1e-9

typedef unsigned long long int ULL;
typedef long long int LL;
typedef pair<int,int> pii;
typedef pair<LL,LL> pll;


inline int setBit(int N, int pos) { return N=N | (1<<pos); }
inline int resetBit(int N, int pos) { return N= N & ~(1<<pos); }
inline bool checkBit(int N, int pos) { return (bool)(N & (1<<pos)); }

//int fx[] = {+0, +0, +1, -1, -1, +1, -1, +1};
//int fy[] = {-1, +1, +0, +0, +1, +1, -1, -1}; //Four & Eight Direction
const int MOD = 1000000007;
#define MAX     20
int edge[MAX+5][MAX+5]; /// edge[u][v] = number of edges between u & v

/*
    ----------------------
*/

inline LL mul(LL u, LL v, LL m = MOD)
{
    LL ret = u * v;
    if(ret >= m) return ret % m;
    return ret;
}

inline LL add(LL u, LL v, LL m = MOD)
{
    return (u + v) % m;
}

inline LL sub(LL u, LL v, LL m = MOD)
{
    LL ret = (u - v) % m;
    if(ret < 0) ret += m;
    return ret;
}

LL ip(LL a, LL p, LL m = MOD)
{
    if(!p) return 1;
    if(p & 1) return mul(a, ip(a, p - 1, m), m);
    LL ret = ip(a, p/2, m);
    return mul(ret, ret, m);
}

inline LL mod_inv(LL v, LL m = MOD){return ip(v, m - 2, m);}



inline int gauss(vector < vector < int > > &A,  int m){
    int eqn = A.size();
    int var = A.back().size() - 1, i, j;
    vector<int> where;
    where.resize(var, -1);
    LL c, d = 1, ret = 1;


    for(int clm = 0, row = 0; clm < var && row < eqn; clm++){
        if(!A[row][clm])
            for(i = row + 1; i < eqn; i++)
                if(A[i][clm]) {
                    for(j = 0; j <= var; j++)
                        swap(A[i][j], A[row][j]);
                    d = (-d) % m;
                    if(d < 0) d += m;

                    break;
                }

        if(!A[row][clm]) {continue;}
        where[clm] = row;

        for(c = mod_inv(A[row][clm], m), i = 0, d = mul(d, c, m); i <= var; i++) {
            A[row][i] = mul( A[row][i] , c , m);
        }

        for(i = 0; i < eqn; i++)
            if(i == row) continue;
            else
                for(c = A[i][clm], j = 0; j <= var; j++) {
                        A[i][j] = sub(A[i][j] , mul(A[row][j] , c, m), m);
                    }
        row++;
    }

    for(i = 0; i < eqn; i++)
        ret = mul(ret, A[i][i], m);

    d = mod_inv(d, m);
    return mul(ret, d, m);
}
vector< vector<int> > A, B;
int deg[MAX+5];

inline LL kirchoff(int n, int m)
{
    if(n == 1) return 1;
    A.clear();
    A.resize(n);
    memset(deg, 0, sizeof(deg));

    for(int i = 0; i < n; i++) A[i].resize(n + 1);

    for(int u = 1; u <= n; u++)
        for(int v = u + 1; v <= n; v++){
            deg[u - 1] = add(deg[u - 1], edge[u][v], m), deg[v - 1] = add(deg[v - 1], edge[u][v], m);
            A[u - 1][v - 1] = A[v - 1][u - 1] = (-edge[u][v] % m + m) % m;
        }

    for(int i = 0; i < n; i++)
        A[i][i] = deg[i];


    B.clear();
    B.resize(n - 1);
    for(int i = 0; i < (int) B.size(); i++)
    {
        B[i].resize((int) A[i].size() - 1);
        for(int j = 0; j < (int) B[i].size(); j++)
            B[i][j] = A[i][j];
    }
    return gauss(B, m);
}



int n, m;

int dp[(1<<17)+5][18];
int vis[(1<<17)+5][18];
bool can[20][20];
vector<int>E[20];
int ways[(1<<17)+5];
int solve(int mask)
{
    if(ways[mask] != -1)
        return ways[mask];
    int &ret = ways[mask];
    if(__builtin_popcount(mask) < 3)
        return ret = 0;
    mem(edge, 0);
    int id[20], cur = 1;
    for(int i = 0; i<n; i++)
    {
        if(checkBit(mask, i))
            id[i] = 1;
        else
            id[i] = ++cur;
    }
    for(int i = 0; i<n; i++)
    {
        for(auto v: E[i])
        {
            int uu = id[i];
            int vv = id[v];
            edge[uu][vv]++;
        }
    }
    return ret = kirchoff(cur, MOD);
}

int firstNode, cs;
int call(int mask, int node)
{
    int &ret = dp[mask][node];
    if(vis[mask][node] == cs)
        return ret;
    vis[mask][node] = cs;
    ret = 0;
    if(can[node][firstNode])
        ret = add(ret, solve(mask));
    for(auto v: E[node])
    {
        if(v > firstNode && checkBit(mask, v) == false)
            ret = add(ret, call(setBit(mask, v), v));
    }
    return ret;
}

int main()
{
//    freopen("maxon.txt","r",stdin);
//    freopen("input.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    sff(n, m);
    mem(ways, -1);
    for(int i = 0; i<m; i++)
    {
        int u, v;
        sff(u, v);
        u--, v--;
        E[u].pb(v);
        E[v].pb(u);
        can[u][v] = can[v][u] = 1;
    }
    int ret = 0;
    for(int i = 0; i<n; i++)
        firstNode = i, cs++, ret = add(ret, call(setBit(0, i), i));
    ret = mul(ret, ip(2, MOD-2, MOD));
    printf("%d\n",ret);
    return 0;
}

