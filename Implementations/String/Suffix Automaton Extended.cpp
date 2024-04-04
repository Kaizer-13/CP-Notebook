/***
    * N = maximum possible string size
    * There won't be more that 2N - 1 nodes
    * There won't be more that 3N - 4 transitions
    * nodes are numbered from 0 to sz-1

    * scan sa::str
    * n = strlen(str)
    * call sa::build(n)

    * let's suppose sub_i represents the maximum substring that is endpos equivalent to node i
    * cnt[i] = number of occurrences of sub_i in str
    * If terminal[i] = true, then sub_i is a suffix of str

    *************************************************************************
    * dp[i] = number of substrings that has sub_i as prefix                 *
    *         The substrings don't need to be unique                        *
    * lex_kth_substr(k) returns the lexicographically k'th substring of str *
    *************************************************************************

***/
namespace sa{
    const int MAXN = 100005 << 1; /// 2 * maximum possible string size
    const int MAXC = 26; /// Size of the character set

    char str[MAXN];

    int n, sz, last; /// sz = number of nodes in the automaton( node indexing is 0 based)
    int len[MAXN], link[MAXN], ed[MAXN][MAXC], cnt[MAXN];
    bool terminal[MAXN];
    vector <int> G[MAXN];

    void init() {
        SET(ed[0]);
        len[0] = 0, link[0] = -1, sz = 1, last = 0, terminal[0] = false;
    }

    inline int scale(char c) { return c-'a'; }

    void extend(char c) {
        int cur = sz++;

        terminal[cur] = false;
        cnt[cur] = 1;

        SET(ed[cur]);
        len[cur] = len[last] + 1;
        int p = last;
        while (p != -1 && ed[p][c]==-1) {
            ed[p][c] = cur;
            p = link[p];
        }
        if (p == -1) link[cur] = 0;
        else {
            int q = ed[p][c];
            if (len[p] + 1 == len[q]) link[cur] = q;
            else {
                int clone = sz++;
                len[clone] = len[p] + 1;
                memcpy(ed[clone],ed[q],sizeof(ed[q]));
                link[clone] = link[q];
                while (p != -1 && ed[p][c] == q) {
                    ed[p][c] = clone;
                    p = link[p];
                }
                link[q] = link[cur] = clone;

                cnt[clone] = 0;
                terminal[clone] = false;
            }
        }
        last = cur;
    }

    /// needed to generate cnt[]
    void dfs(int s) {
        for(auto x : G[s]) dfs(x), cnt[s] += cnt[x];
    }

    ll dp[MAXN];
    ll call(int nd) {
        ll &ret = dp[nd];
        int x;
        if(ret!=-1) return ret;
        ret = cnt[nd];
        for(int i=0;i<MAXC;i++) {
            x = ed[nd][i];
            if(x!=-1) ret += call(x);
        }
        return ret;
    }



    /// returns the lexicographically k'th substring of str
    string lex_kth_substr(ll k) {
        if((k+k) > (n*(n+1LL))) return "No such line.";
        string ret = "";
        int cur = 0, x;
        while(k>0) {
            for(int i=0;i<MAXC;i++) {
                x = ed[cur][i];
                if(x == -1) continue;
                if(call(x)>=k) {
                    ret += (char)i + 'a';
                    cur = x;
                    k -= cnt[x];
                    break;
                }
                k -= call(x);
            }
        }
        return ret;
    }


    void build() {
        init();
        n = strlen(str);
        for(int i=0;i<n;i++) extend(scale(str[i]));

        /// construction of cnt array
        for(int i=1;i<sz;i++) G[link[i]].pb(i);
        dfs(0);
        for(int i=0;i<sz;i++) G[i].clear();

        /// construction of terminal array
        for(int i=last;i!=-1;i=link[i]) terminal[i] = true;

        /// lex_kth_substr
        SET(dp);
    }
}
