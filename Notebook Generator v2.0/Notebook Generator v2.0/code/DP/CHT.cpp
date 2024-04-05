
/**
 *   Lines should be added non-increasing order of m for minimizing
 Non-decreasing order of m for maximizing
 *   Intersection point of two lines (m1,c1) , (m2,c2) is
 x = (c2-c1)/(m1-m2)
 **/

ll M[MAX] , C[MAX];

struct CHT {
  int len , cur;
  void init() {
    len = 0 ,cur = 0;
  }

  /// returns true if line[len-1] is unnecessary when we add line(nm,nc)
  inline bool isBad(ll nm,ll nc) {
    return ( (C[len-1]-C[len-2])/(double)(M[len-2]-M[len-1]) >= (nc-C[len-2])/(double)(M[len-2]-nm) );
    //return ( (C[len-1]-C[len-2])*(M[len-2]-nm) >= (M[len-2]-M[len-1])*(nc-C[len-2]) );
  }

  inline void addLine(ll nm,ll nc) {
    if(len == 0) M[len] = nm , C[len] = nc , ++len;
    else if( M[len-1] == nm ) {
      if(C[len-1] <= nc) return; /// <= to minimize, >= to maximize
      else C[len-1] = nc;
    }
    else {
      while(len >= 2 && isBad(nm,nc)) --len;
      M[len] = nm , C[len] = nc , ++len;
    }
  }

  inline ll getY(int id , ll x) {
    return ( M[id]*x + C[id] );
  }

  inline ll sortedQuery( ll x ) {
    if(cur >= len ) cur = len-1;
    while( cur < len-1 && getY(cur+1,x) >= getY(cur,x) ) cur++; /// <= to minimize, >= to maximize
    return getY(cur,x);
  }

  inline ll TS( ll x ) {
    int low = 0, high = len-1 , mid ;
    while( high - low > 1 ) {
      mid = low + high >> 1;
      if(getY(mid,x) < getY(mid+1,x)) low = mid + 1; /// > to minimize , < to maximize
      else high = mid;
    }
    return max(getY(low,x),getY(high,x)); /// adjust min/max
  }
};

CHT cht;
cht.init();

