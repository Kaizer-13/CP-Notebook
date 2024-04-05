struct HopcroftKarp {
  const int N, M;
  std::vector<std::vector<int>> adj_left;
  std::vector<int> matchL, matchR;

  HopcroftKarp(int N, int M, const std::vector<std::pair<int, int>>& edge)
      : N(N), M(M), matchL(N, -1), matchR(M, -1), adj_left(N) {
    for (auto [l, r] : edge)
      adj_left[l].push_back(r);
  }

  int maxmatching() {
    int sz = 0;
    for (bool updated = true; updated;) {
      updated = false;
      static std::vector<int> root(N), prev(N), qq(N);
      static int qi, qj;
      // std::queue<int> q;
      qi = qj = 0;
      std::fill(root.begin(), root.end(), -1),
      std::fill(prev.begin(), prev.end(), -1);
      for (int i = 0; i < N; i++)
        if (matchL[i] == -1)
          qq[qj++] = i, root[i] = i, prev[i] = i;
      // q.push(i), root[i] = i;
      while (qi < qj) {
        int u = qq[qi++];
        // int u = q.front(); q.pop();
        if (matchL[root[u]] != -1) continue;
        for (int v : adj_left[u]) {
          if (matchR[v] == -1) {
            while (v != -1)
              matchR[v] = u, std::swap(matchL[u], v), u = prev[u];
            updated = true, sz++;
            break;
          }
          if (prev[matchR[v]] == -1)
            v = matchR[v], prev[v] = u, root[v] = root[u], qq[qj++] = v;
          // v = matchR[v], prev[v] = u, root[v] = root[u], q.push(v);
        }
      }
    }
    return sz;
  }
};
