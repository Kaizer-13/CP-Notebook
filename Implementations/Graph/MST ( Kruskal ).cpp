struct edge {
    int u, v, c;
} ara[MAX];

bool cmp(edge a,edge b) { return a.c < b.c;}
int par[MAX];

int findParent(int u) {
    if(par[u] == u) return u;
    else return par[u] = findParent(par[u]);
}

int kruskal(int n, int m) {
    sort (ara + 1, ara + m + 1, cmp);
    int i, mst;
    mst = 0;
    for(i = 1; i <= n; i++) par[i] = i;
    for(i = 1; i <= m; i++) {
        edge x = ara[i];
        par[x.u] = findParent(x.u);
        par[x.v] = findParent(x.v);
        if(par[x.u] != par[x.v]){
            par[par[x.u]] = par[x.v];
            mst += x.c;
        }
    }
    return mst;
}