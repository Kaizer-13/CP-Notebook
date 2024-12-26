struct node{
  vector<int> vc;
  node(int x = 0){
    if (x) vc.push_back(x);
  }
  node operator+(const node &other){
    node ret;
    ret.vc = vc;
    for (int x : other.vc) ret.vc.push_back(x);
    sort(ret.vc.begin(), ret.vc.end());
    return ret;
  }
};
node t[4 * M];
void build(int a[], int v, int tl, int tr){
  if (tl == tr){
    t[v] = node(a[tl]);
    return;
  }
  int tm = (tl + tr) / 2;
  build(a, v * 2, tl, tm);
  build(a, v * 2 + 1, tm + 1, tr);
  t[v] = t[v * 2] + t[v * 2 + 1];
}
int query(int v, int tl, int tr, int l, int r, int x){
  if (l > tr or r < tl) return 0;
  if (l <= tl and tr <= r){
    int ret;
    // do your thing with x here
    return ret;
  }
  int tm = (tl + tr) / 2;
  int Lchild = query(v * 2, tl, tm, l, r, x);
  int Rchild = query(v * 2 + 1, tm + 1, tr, l, r, x);
  return Lchild + Rchild;
}