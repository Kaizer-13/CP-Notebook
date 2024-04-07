/*
 * Everything is 0 based
 * Call precal() once in the program
 * Call update(1,0,n-1,i,j,val) to update the value of position
 i to j to val, here n is the length of the string
 * Call query(1,0,n-1,L,R) to get a node containing hash
 of the position [L:R]
 * Before any update/query
 - Call init(str) where str is the string to be hashed
 - Call build(1,0,n-1)
 */

#define INVALID_CHAR        -1

namespace strhash {
  int n;
  const int MAX = 100010;
  int ara[MAX];
  const int MOD[] = {1067737007, 1069815139};
  const int BASE[] = {982451653, 984516781};


  int BP[2][MAX], CUM[2][MAX];

  void init(char *str) {
    n = strlen(str);
    for(int i=0;i<n;i++) ara[i] = str[i]-'0'+1; // scale str[i] if needed
  }

  void precal() {
    BP[0][0] = BP[1][0] = 1;
    CUM[0][0] = CUM[1][0] = 1;
    for(int i=1;i<MAX;i++) {
      BP[0][i] = ( BP[0][i-1] * (long long) BASE[0] ) % MOD[0];
      BP[1][i] = ( BP[1][i-1] * (long long) BASE[1] ) % MOD[1];

      CUM[0][i] = ( CUM[0][i-1] + (long long) BP[0][i] ) % MOD[0];
      CUM[1][i] = ( CUM[1][i-1] + (long long) BP[1][i] ) % MOD[1];
    }
  }

  struct node {
    int sz;
    int h[2];
    node() {}
  } tree[4*MAX];

  int lazy[4*MAX];

  inline void lazyUpdate(int n,int st,int ed) {
    if(lazy[n]!=INVALID_CHAR){

      tree[n].h[0] = (lazy[n] * (long long) CUM[0][ed-st]) % MOD[0];
      tree[n].h[1] = (lazy[n] * (long long) CUM[1][ed-st]) % MOD[1];

      if(st!=ed){
        lazy[2*n] = lazy[n];
        lazy[2*n+1] = lazy[n];
      }
      lazy[n] = INVALID_CHAR;
    }
  }

  inline node Merge(node a,node b) {
    node ret;

    ret.h[0] = ( ( a.h[0] * (long long) BP[0][b.sz] ) + b.h[0] ) % MOD[0];
    ret.h[1] = ( ( a.h[1] * (long long) BP[1][b.sz] ) + b.h[1] ) % MOD[1];

    ret.sz = a.sz + b.sz;

    return ret;
  }

  inline void build(int n,int st,int ed) {
    lazy[n] = INVALID_CHAR;
    if(st==ed) {
      tree[n].h[0] = tree[n].h[1] = ara[st];
      tree[n].sz = 1;
      return;
    }
    int mid = (st+ed)>>1;
    build(n+n,st,mid);
    build(n+n+1,mid+1,ed);

    tree[n] = Merge(tree[n+n],tree[n+n+1]);
  }


  inline void update(int n,int st,int ed,int i,int j,int v) {
    lazyUpdate(n,st,ed);
    if(st>j or ed<i) return;
    if(st>=i and ed<=j) {
      lazy[n] = v;
      lazyUpdate(n,st,ed);
      return;
    }

    int mid = (st+ed)>>1;
    update(n+n,st,mid,i,j,v);
    update(n+n+1,mid+1,ed,i,j,v);

    tree[n] = Merge(tree[n+n],tree[n+n+1]);
  }

  inline node query(int n,int st,int ed,int i,int j){
    lazyUpdate(n,st,ed);
    if(st>=i and ed<=j) return tree[n];
    int mid = (st+ed)/2;
    if(mid<i) return query(n+n+1,mid+1,ed,i,j);
    else if(mid>=j) return query(n+n,st,mid,i,j);
    else return Merge(query(n+n,st,mid,i,j),query(n+n+1,mid+1,ed,i,j));
  }
}

