/*
need LCA template to answer queries.
can answer queries like mo for each path (u, v) in the tree as they can be mapped to a range in the flattened dfs-order traversal array.
a node is not on the path (u, v) if it appears 0 or 2 times in the corresponding range.
WLOG assume tin[u] <= tin[v]. let p = LCA(u, v). in case p!=u, need to include value of p in answer as its not in the range [tout[u], tin[v]];
*/
const int B = 450; //define B close to sqrt(n)
int cnt[M], order[2*M], tin[M], tout[M], timer;
void dfs(int u, int p){
  tin[u] = ++timer;
  order[timer] = u;
  for(int v : g[u]){
    if(v != p){
      dfs(v, u);
    }
  }
  tout[u] = ++timer;
  order[timer] = u;
}
pii range(int u, int v, int &p){
  if(tin[u] > tin[v]) swap(u, v);
  p = LCA::LCA(u, v);
  if(p == u){
    p = -1;
    return make_pair(tin[u], tin[v]);
  }
  return make_pair(tout[u], tin[v]);
}
void add_node(int v)
void remove_node(int v)
void process(int idx){
  int x = order[idx];
  if(cnt[x]) remove_node(x);
  else add_node(x);
  cnt[x] ^= 1;
} 
ll get_answer(int p){
  //if p != -1, include value of p in answer
}
struct query{
  int l, r, idx, p;
  query(){};
  query(int u, int v, int idx) : idx(idx){
    auto [L, R] = range(u, v, p);
    l = L, r = R;
  };
  bool operator <(const query &other){
    if(l/B == other.l/B){
      if((l/B) & 1) return r > other.r;
      else return other.r > r;
    }
    return l < other.l;
  }
};
vector<ll>mo(vector<query>queries){
  vector<ll>answers(queries.size());
  sort(queries.begin(), queries.end());
  int cur_l = 1, cur_r = 0;
  for(auto q : queries){
    while(cur_l > q.l){
      cur_l--;
      process(cur_l);
    }
    while(cur_r < q.r){
      cur_r++;
      process(cur_r);
    }
    while(cur_l < q.l){
      process(cur_l);
      cur_l++;
    }
    while(cur_r > q.r){
      process(cur_r);
      cur_r--;
    }
    answers[q.idx] = get_answer(q.p);
  }
  return answers;
}