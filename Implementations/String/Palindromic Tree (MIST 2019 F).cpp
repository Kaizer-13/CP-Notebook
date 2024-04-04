#include <bits/stdc++.h>
using namespace std;
#define CLR(a) memset(a,0,sizeof a)
#define pb push_back

int base, mod;
inline int add(int a,int b) { return (a + 0LL + b) % mod; }
inline int mul(int a,int b) { return (a * 1LL * b) % mod; }

int ans[1000010];

namespace pt {
    const int MAXN = 1000010;
    const int MAXC = 26;

    int n;
    char str[MAXN];
    int len[MAXN], link[MAXN], ed[MAXN][MAXC], occ[MAXN], st[MAXN];

    int nc, suff, pos;

    void init() {
        str[0] = -1;
        nc = 2; suff = 2;
        len[1] = -1, link[1] = 1;
        len[2] =  0, link[2] = 1;
        CLR(ed[1]), CLR(ed[2]);
        occ[1] = occ[2] = 0;
    }

    inline int scale(char c) { return c-'a'; }

    inline int nextLink(int cur) {
        while (str[pos - 1 - len[cur]] != str[pos]) cur = link[cur];
        return cur;
    }

    inline bool addLetter(int p) {
        pos = p;
        int let = scale(str[pos]);
        int cur = nextLink(suff);

        if (ed[cur][let]) {
            suff = ed[cur][let];
            occ[suff]++;
            return false;
        }

        suff = ++nc;
        CLR(ed[nc]);
        len[nc] = len[cur] + 2;
        ed[cur][let] = nc;
        occ[nc] = 1;

        if (len[nc] == 1) {
            st[nc] = pos;
            link[nc] = 2;
            return true;
        }
        link[nc] = ed[nextLink(link[cur])][let];
        st[nc] = pos-len[nc] + 1;
        return true;
    }

    int sub[MAXN], shuru[MAXN], shesh[MAXN];
    int Time = 0;
    void dfs(int s) {
        shuru[s] = ++Time, sub[s] = occ[s];
        for(int i=0;i<26;i++) {
            if(ed[s][i]) {
                dfs(ed[s][i]);
                sub[s] = add(sub[s],sub[ed[s][i]]);
            }
        }
        shesh[s] = ++Time;
    }
    vector <int> G[MAXN];
    bool cmp(int a,int b) { return shuru[a] < shuru[b]; }

    void traverse(int s) {
        int done = 0;
        sort(G[s].begin(),G[s].end(),cmp);
        for(int x : G[s]) {
            if(shuru[x]>shuru[s] and shesh[x]<shesh[s]) traverse(x);
            else if(shuru[x] <= done) traverse(x);
            else{
                done = shesh[x];
                sub[s] = add(sub[s],sub[x]);
                traverse(x);
            }
        }
        ans[len[s]] = add(ans[len[s]],mul(occ[s],sub[s]));
    }
    void build(int _n) {
        n = _n;
        init();
        for(int i=1;i<=n;i++) addLetter(i);
        for(int i=nc;i>=3;i--) occ[link[i]] += occ[i];
        occ[1] = occ[2] = 0;
        Time = 0;
        dfs(1), dfs(2);
        for(int i=2;i<=nc;i++) G[link[i]].pb(i);
        traverse(1);
        for(int i=1;i<=nc;i++) G[i].clear();
    }
}

int poww[1000010];

int main() {
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);

    int T,n;
    scanf("%d",&T);
    for(int t=1;t<=T;t++) {
        scanf("%d %d %d",&n,&base,&mod);
        CLR(ans);

        scanf("%s",pt::str+1);
        pt::build(strlen(pt::str+1));

        poww[0] = 1;
        for(int i=1;i<=n;i++) poww[i] = mul(poww[i-1],base);
        int res = 0;
        for(int i=1;i<=n;i++) {
            res = add(res,mul(poww[n-i],ans[i]));
        }
        printf("Case %d: %d\n",t,res);
    }
    return 0;
}
