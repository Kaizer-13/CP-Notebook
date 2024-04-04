vector <pii> ed[MAX];
int dis[MAX];
bool vis[MAX];
priority_queue <pii> Q;

void dijkstra(int s, int n) {

    for(int i=1;i<=n;i++) dis[i] = INF, vis[i] = false;
    dis[s] = 0;
    Q.emplace(0, s);
    int u, v, w, d;
    while(!Q.empty()){
        auto e = Q.top();
        u = e.yy, d = e.xx;
        Q.pop();
        if(!vis[u]){
            vis[u] = true;
            for(auto e : ed[u]) {
                v = e.xx, w = e.yy;
                if(dis[v] > dis[u] + w) {
                    dis[v] = dis[u] + w;
                    Q.emplace(-dis[v], v);
                }
            }
        }
    }
}
