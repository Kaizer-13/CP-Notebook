// O(V^2 sqrt(E))
// 0 based node indexing

#include <bits/stdc++.h>
using namespace std;
using T = long long;

struct Edge {
    int to, back;
    T f, c;
};

struct PushRelabel {
    vector <vector <Edge>> ed;
    vector <T> ec;

    vector <Edge*> cur;
    vector < vector <int>> hs;
    vector <int> H;

    PushRelabel(int n) : ed(n), ec(n), cur(n), hs(2*n), H(n) {}

    void addEdge(int s, int t, T cap, T rcap = 0) {
        if (s == t) return;
        ed[s].push_back({t, ed[t].size(), 0, cap});
        ed[t].push_back({s, (int)ed[s].size()-1, 0, rcap});
    }

    void addFlow(Edge& e, T f) {
        Edge &back = ed[e.to][e.back];

        if (!ec[e.to] && f) hs[H[e.to]].push_back(e.to);
        e.f += f, e.c -= f;
        ec[e.to] += f;
        back.f -= f, back.c += f;
        ec[back.to] -= f;
    }

    T maxFlow(int s, int t) {
        int v = ed.size();
        H[s] = v;
        ec[t] = 1;
        vector <int> co(2*v);
        co[0] = v-1;
        for(int i=0;i<v;i++) cur[i] = ed[i].data();
        for(auto &e : ed[s]) addFlow(e, e.c);
        for (int hi = 0;;) {
            while (hs[hi].empty()) if (!hi--) return -ec[s];
            int u = hs[hi].back();
            hs[hi].pop_back();
            while (ec[u] > 0) {
                if (cur[u] == ed[u].data() + ed[u].size()) {
                    H[u] = 1e9;
                    for(auto &e : ed[u]) {
                        if (e.c && H[u] > H[e.to]+1) H[u] = H[e.to]+1, cur[u] = &e;
                    }
                    if (++co[H[u]], !--co[hi] && hi < v) {
                        for(int i=0;i<v;i++) {
                            if (hi < H[i] && H[i] < v) --co[H[i]], H[i] = v + 1;
                        }
                    }
                    hi = H[u];
                }
                else if (cur[u]->c && H[u] == H[cur[u]->to]+1) addFlow(*cur[u], min(ec[u], cur[u]->c));
                else ++cur[u];
            }
        }
    }
};

int main()
{
    int n, m, u, v, c;
    cin >> n >> m;

    PushRelabel flow(n);

    for(int i=0;i<m;i++) {
        cin >> u >> v >> c;
        u--, v--;
        flow.addEdge(u, v, c, c);
    }

    cout << flow.maxFlow(0, n - 1) << '\n';
    return 0;
}

