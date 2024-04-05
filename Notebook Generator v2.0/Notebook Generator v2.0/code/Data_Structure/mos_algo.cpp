struct data{
  int l, r, id, bn;
  data() {}
  data(int _l, int _r, int _id){
    l = _l, r = _r, id = _id;
    bn = l / block_sz;
  }
  bool operator < (const data& other) const{
    if (bn != other.bn) return (bn < other.bn);
    return ((bn & 1) ? (r < other.r) : (r > other.r));
  }

}

int curL = 0, curR = -1;
for(int i = 0; i < Q.sz; i++){
  while(curL > Q[i].L){
    curL--; add(curL);
  }
  while(curR < Q[i].R){
    curR++; add(curR);
  }
  while(curL < Q[i].L){
    remove(curL); curL++;
  }
  while(curR > Q[i].R){
    remove(curR); curR--;
  }
}
