ll bit[M];
int sz;
void update(int idx, ll val){
  while(idx <= sz){
    bit[idx] += val;
    idx += (idx & -idx);
  }
}
ll query(int R){
  ll ret = 0;
  while(R > 0){
    ret += bit[R];
    R -= (R & -R);
  }
  return ret;
}
ll query(int L, int R){
  if(L > R) return 0;
  return query(R) - query(L-1);
}