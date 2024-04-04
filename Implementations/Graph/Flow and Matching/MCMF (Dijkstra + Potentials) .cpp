/***
    * 1 based node indexing
    * call init at the start of every test case
    * Sparse graph, amount of flow is low
***/

namespace mcmf {
    using T = int;
    const T INF = ?; /// 0x3f3f3f3f or 0x3f3f3f3f3f3f3f3fLL
    const int MAX = ?; /// maximum number of nodes

    int n, src, snk;
    bool vis[MAX];
    int par[MAX], pos[MAX];
    T pot[MAX], dis[MAX], mCap[MAX];
    priority_queue < pair <T, int> > q;

    struct Edge {
        int to, rev_pos;
        T cap, cost, flow;
    };
    vector <Edge> ed[MAX];

    void init(int _n,int _src,int _snk) {
        n = _n, src = _src, snk = _snk;
        for(int i=1;i<=n;i++) ed[i].clear();
    }

    void addEdge(int u,int v,T cap,T cost){
        Edge a = {v,ed[v].size(),cap,cost,0};
        Edge b = {u,ed[u].size(),0,-cost,0};
        ed[u].pb(a);
        ed[v].pb(b);
    }


    T BellmanDP(int u) {
        if (vis[u]) return pot[u];
        if (u == src) {
            pot[src] = 0; return 0;
        }
        vis[u] = true;
        pot[u] = INF;
        for (Edge e : ed[u]){
            Edge r = ed[e.to][e.rev_pos];
            if( r.flow < r.cap )
                pot[u] = min(pot[u], BellmanDP(e.to) + r.cost);
        }

        return pot[u];
    }


    // Dijkstra
    bool augment() {
        memset(vis, 0, (n + 1) * sizeof(bool));
        for (int i=1;i<=n;i++) dis[i] = mCap[i] = INF;
        dis[src] = 0;
        q.push({0, src});

        int u, v;
        while (!q.empty()) {
            u = q.top().yy;
            q.pop();
            if (vis[u]) continue;
            vis[u] = true;

            int ptr = 0;
            for(Edge e : ed[u]) {
                v = e.to;
                T cost = e.cost + pot[u] - pot[v];
                if (e.flow < e.cap && dis[u] + cost < dis[v]) {
                    dis[v] = dis[u] + cost;
                    par[v] = u;
                    pos[v] = ptr;
                    mCap[v] = min(mCap[u],e.cap-e.flow);
                    q.push(make_pair(-dis[v], v));
                }
                ++ptr;
            }
        }
        for (int i=1;i<=n;i++) dis[i] += (pot[i] - pot[src]);
        return vis[snk];
    }

    // JohnsonDinic
    pair <T, T> solve() {
        memset(pot, 0, (n+1)*sizeof(T));
        memset(vis, 0, (n+1)*sizeof(bool));
        BellmanDP(snk);
        int u, v;
        T F = 0, C = 0, f;
        while( augment() ) {
            u = snk;
            f = mCap[snk];
            while (u != src) {
                v = par[u];
                ed[v][pos[u]].flow += mCap[snk]; /// edge of v-->u increases
                ed[u][ed[v][pos[u]].rev_pos].flow -= mCap[snk];
                u = v;
            }
            F += f;
            C += f * dis[snk];
            memcpy(pot, dis, (n + 1) * sizeof(T));
        }
        return mp(F,C);
    }
}

