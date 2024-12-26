//set N = 4*Q*log2(n) where Q = maximum no. of queries you will perform.
int get(int l, int r){
  //whatever you need here
}
struct segtree_implicit{
    
	int t[N], lazy[N];
	int n, sz;
	int lc[N], rc[N];
	segtree_implicit(int n=0) : n(n){
		sz = 1;
		t[sz] = get(1, n);
		lazy[sz] = -1;
		lc[sz] = rc[sz] = 0;
	};
	void create(int &node, int l, int r){
		if(node) return;
		node = ++sz;
		t[node] = get(l, r);
		lazy[node] = -1;
		lc[node] = rc[node] = 0;
	}
	void push(int v, int tl, int tr){

		if(lazy[v] == -1) return; //for assignment
		t[v] = (tr-tl+1)*lazy[v];
		if(tl != tr){
			int tm = (tl + tr) / 2;
			create(lc[v], tl, tm);
			create(rc[v], tm+1, tr);
			lazy[lc[v]] = lazy[rc[v]] = lazy[v];
		}
		lazy[v] = -1;
	}
	void update(int v, int tl, int tr, int l, int r, int val){
		push(v, tl, tr);
		if(l > tr or r < tl) return;
		if(l <= tl and tr <= r){
			lazy[v] = val;
			push(v, tl, tr);
			return;
		}
		int tm = (tl + tr) / 2;
		create(lc[v], tl, tm);
		create(rc[v], tm+1, tr);
		update(lc[v], tl, tm, l, r, val);
		update(rc[v], tm+1, tr, l, r, val);
		t[v] = t[lc[v]] + t[rc[v]];
	}
	void update(int l, int r, int val){
		update(1, 1, n, l, r, val);
	}
	int query(int v, int tl, int tr, int l, int r){
		push(v, tl, tr);
		if(l > tr or r < tl) return 0;
		if(l <= tl and tr <= r) return t[v];
		int tm = (tl + tr) / 2;
		create(lc[v], tl, tm);
		create(rc[v], tm+1, tr);
		int lchild = query(lc[v], tl, tm, l, r);
		int rchild = query(rc[v], tm+1, tr, l, r);
		return lchild + rchild;
	}
	int query(int l, int r){
		return query(1, 1, n, l, r);
	}
};