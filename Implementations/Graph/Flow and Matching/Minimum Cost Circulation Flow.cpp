// Given a directed weighted graph, computes the minimum cost to run the maximum
// amount of circulation flow through the graph(no source/sink needed)
// minimizes thes cost, then maximizes the flow
// If all the costs are positive, returns 0
// works for negative cycle
// call init() before the start of every test case
// run() runs the algorithm and returns total cost


#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define REP(i, n) FOR(i, 0, n)

/*************** 0 based node indexing **************/

namespace mccf {
    const int MAXV = 310;
    const int MAXE = 1000100; // 2 * maximum number of edges
    int V, E;
    int how[MAXV], good[MAXV], bio[MAXV], cookie = 1;
    ll dist[MAXV];
    int from[MAXE], to[MAXE];
    ll cap[MAXE], cost[MAXE];
    void init(int n) {
        V = n;
        E = 0;
    }
    void addEdge(int x, int y, ll cp, ll cst) {
        from[E] = x, to[E] = y, cap[E] = cp, cost[E] = cst; ++E;
        from[E] = y, to[E] = x, cap[E] = 0, cost[E] = -cst; ++E;
    }
    void reset() {
        REP(i, V) dist[i] = 0;
        REP(i, V) how[i] = -1;
    }
    bool relax() {
        bool ret = false;
        REP(e, E) {
            if (cap[e]) {
                int x = from[e];
                int y = to[e];
                if (dist[x] + cost[e] < dist[y]) {
                    dist[y] = dist[x] + cost[e];
                    how[y] = e;
                    ret = true;
                }
            }
        }
        return ret;
    }
    ll cycle(int s, bool flip = false) {
        int x = s;
        ll c = cap[how[x]];
        do {
            int e = how[x];
            c = min(c, cap[e]);
            x = from[e];
        } while (x != s);
        ll sum = 0;
        do {
            int e = how[x];
            if (flip) {
                cap[e] -= c;
                cap[e ^ 1] += c;
            }
            sum += cost[e] * c;
            x = from[e];
        } while (x != s);
        return sum;
    }
    ll push(int x) {
        for (++cookie; bio[x] != cookie; x = from[how[x]]) {
            if (!good[x] || how[x] == -1 || cap[how[x]] == 0) return 0;
            bio[x] = cookie;
            good[x] = false;
        }
        return cycle(x) >= 0 ? 0 : cycle(x, true);
    }
    ll run() {
        reset();
        ll ret = 0;
        REP(step, 2 * V) {
            if (step == V) reset();
            if (!relax()) continue;
            REP(i, V) good[i] = true;
            REP(i, V) if (ll w = push(i)) ret += w, step = 0;
        }
        return ret;
    }
}
