/***
    * Edmonds Carp Algorithm
    * Finds Max Flow using ford fulkerson method
    * Finds path from source to sink using bfs
    * Complexity V*E*E
***/

vector <int> ed[MAX];
int cap[MAX][MAX];
int par[MAX]; ///keeps track of the parent in a path from s to d
int mCap[MAX]; ///mCap[i] keeps track edge that have minimum cost on the shortest path from s to i

bool getPath(int s,int d,int n){
    for(int i=0; i<=n; i++) mCap[i] = INF;
    SET(par);
    queue <int> q;
    q.push(s);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int i=0; i<ed[u].size(); i++){
            if(cap[u][ed[u][i]]!=0 && par[ed[u][i]]==-1){
                par[ed[u][i]] = u;
                mCap[ed[u][i]] = min(mCap[u],cap[u][ed[u][i]]);
                if(ed[u][i]==d) return true;
                q.push(ed[u][i]);
            }
        }
    }
    return false;
}

int getFlow(int s,int d,int n){
    int F = 0;
    while(getPath(s,d,n)){
        int f = mCap[d];
        F += f;
        int u = d;
        while(u!=s){
            int v = par[u];
            cap[u][v] += f;
            cap[v][u] -= f;
            u = v;
        }
    }
    return F;
}

int main(){
    int maxFlow = getFlow(s,d,n);
    return 0;
}
