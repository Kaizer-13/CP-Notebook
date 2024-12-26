//complexity : O(Fnm)

struct edge{
  int v, rev_pos;
  ll cap, cost, flow = 0;
};

struct MCMF{
  
  int n, s, t;
  vector<vector<edge>>E;

  vector<int>vis, par, pos;
  vector<ll>caps, dist;

  MCMF(int n, int s, int t) : n(n), s(s), t(t), E(n), vis(n), par(n), pos(n), caps(n), dist(n){}

  inline void add_edge(int u, int v, ll cap, ll cost = 0){
    E[u].emplace_back(v, E[v].size(), cap, cost);
    E[v].emplace_back(u, E[u].size() - 1, 0, -cost);
  }

  bool SPFA(){
    vis.assign(n, 0);
    for(int i=0; i<n; i++) caps[i] = dist[i] = INF;
    queue<int>q;
    q.emplace(s), dist[s] = 0, vis[s] = 1;
    while(!q.empty()){
      int i = 0, u = q.front();
      q.pop(), vis[u] = 0;
      for(auto &e : E[u]){
        int v = e.v;
        ll f = e.cap - e.flow, w = dist[u] + e.cost;
        if(f > 0 and dist[v] > w){
          dist[v] = w, par[v] = u, pos[v] = i;
          caps[v] = min(caps[u], f);
          if(!vis[v]){
            q.push(v), vis[v] = 1;
          }
        }
        ++i;
      }
    }
    return dist[t] != INF;
  }

  pll maxflow(){
    ll flow = 0, cost = 0;
    while(SPFA()){
      int v = t;
      ll f = caps[v];
      flow += f;
      while(v ^ s){
        int u = par[v];
        edge &e = E[u][pos[v]];
        e.flow += f;
        E[v][e.rev_pos].flow -= f;
        v = u;
      }
      cost += dist[t] * f;
    }
    return make_pair(flow, cost);
  }
};