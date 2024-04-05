const int N = 3e4 + 5;
vector<int> G[N];
int sz[N], H[N], P[N];

void dfs(int cur, int h)
{
    sz[cur] = 1;
    H[cur] = h;
    for(int& to : G[cur]) {
        G[to].erase(find(G[to].begin(), G[to].end(), cur));
        P[to] = cur;
        dfs(to, h + 1);
        sz[cur] += sz[to];
        if(sz[to] > sz[G[cur][0]]) swap(G[cur][0], to);
    }
}

int base[N], pos[N], head[N];
int ptr = 0;

void hld(int cur)
{
    pos[cur] = ++ptr;
    base[ptr] = cur;
    for(int to : G[cur]) {
        head[to] = (to == G[cur][0] ? head[cur] : to);
        hld(to);
    }
}

segtree ST;

int query(int u, int v)
{
    int ret = 0;
    while(head[u] != head[v]) {
        if(H[head[u]] > H[head[v]]) swap(u, v);
        ret += ST.query(pos[head[v]], pos[v]);
        v = P[head[v]];
    }
    if(H[u] > H[v]) swap(u, v);
    ret += ST.query(pos[u], pos[v]);
    return ret;
}

void update(int u, int val) {
    ST.update(pos[u], val);
}

void build(int n, int root)
{
    ptr = 0;
    dfs(root, 0);
    head[root] = root;
    hld(root);
    ST = segtree(n);
}

/*
 * clear graph
 * call build
 * Prob : sum of values from u to v
 */

