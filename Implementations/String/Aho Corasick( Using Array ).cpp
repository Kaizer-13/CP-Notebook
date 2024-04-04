/***
    Given n patterns and a text T, for every pattern
    you have to output the number of times that pattern
    appears in the text.

    * Don't forget to call build() after adding all the patterns
      to the Aho Corasick trie.

    * ans[i] contains the number of occurrences of the i'th pattern

    * link[x] = y means there is a suffix link from node x to node y

    * out_link[x] = y means we can go from x to y using the suffix links
      suppose the path is as follows : x , a , b, c, ..., y
      No pattern ends in node a, b, c, ... but some pattern ends at node y.

    * After a call to build(), the trie becomes a DAG(except node 0)
      next[x][c] = y means if we are currently at node x and the character
      c arrives, we will go to node y.


    * Suppose sum of the length of the characters is N. Text length is also
      at most N. If all the patterns are unique, total number of occurrences
      of all the patterns will not be more than " N sqrt(N) ".
***/

#include <bits/stdc++.h>

using namespace std;

const int N = ?; /// Total number of characters in pattern
const int A = ?; /// Alphabet size

struct AC {
    int nd, pt;

    int next[N][A], link[N], out_link[N], cnt[N], ans[N];
    vector <int> ed[N], out[N];

    AC(): nd(0), pt(0) { node(); }

    int node() {
        memset(next[nd], 0, sizeof next[nd]);
        link[nd] = out_link[nd] = cnt[nd] = 0;
        ed[nd].clear(), out[nd].clear();
        return nd++;
    }

    void clear() {
        nd = pt = 0;
        node();
    }

    inline int get(char c) { return c - 'a'; }

    void insert(const string &T) {
        int u = 0;
        for (char c : T) {
            if (!next[u][get(c)]) next[u][get(c)] = node();
            u = next[u][get(c)];
        }
        ans[pt] = 0;
        out[u].push_back(pt++);
    }

    void build() {
        queue <int> q;
        for (q.push(0); !q.empty(); ) {
            int u = q.front();
            q.pop();
            for (int c = 0; c < A; ++c) {
                int v = next[u][c];
                if (!v) next[u][c] = next[link[u]][c];
                else {
                    link[v] = u ? next[link[u]][c] : 0;
                    out_link[v] = out[link[v]].empty() ? out_link[link[v]] : link[v];
                    ed[link[v]].push_back(v);
                    q.push(v);
                }
            }
        }
    }

    void dfs(int s) {
        for(int x : ed[s]) dfs(x), cnt[s] += cnt[x];
        for(int e : out[s]) ans[e] = cnt[s];
    }

    void traverse(const string &S) {
        int u = 0;
        for (char c : S) {
            u = next[u][get(c)];
            cnt[u]++;
        }
        dfs(0);
    }
};

char str[1000010], pat[505];

int main() {
//    freopen("in.txt","r",stdin);
    AC aho;
    int t,T;
    scanf("%d",&T);
    for(int t=1;t<=T;t++) {
        int n;
        scanf("%d",&n);
        scanf("%s",str);
        for(int i=1;i<=n;i++) {
            scanf("%s",pat);
            aho.insert(pat);
        }
        aho.build();
        aho.traverse(str);
        printf("Case %d:\n",t);
        for(int i=0;i<n;i++) {
            printf("%d\n",aho.ans[i]);
        }
        aho.clear();
    }
    return 0;
}

