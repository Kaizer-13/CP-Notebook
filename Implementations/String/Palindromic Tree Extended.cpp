#include <bits/stdc++.h>
using namespace std;
#define CLR(a) memset(a,0,sizeof(a))
/***
    *************************************************************
    * depth[nd] = Number of suffixes of P that are palindrome   *
    *             P --> The palindrome representing node nd     *
    *                                                           *
    * fin[i] = Number of palindromes that end at index i        *
    *                                                           *
    * To know start[i], reverse the string and find fin[1...n]  *
    * Then, start[i] = fin[n-i+1] (of the reversed string)      *
    *************************************************************
***/

namespace pt {
    const int MAXN = 100010; /// maximum possible string size
    const int MAXC = 26; /// Size of the character set

    int n; /// length of str
    char str[MAXN];
    int len[MAXN], link[MAXN], ed[MAXN][MAXC], occ[MAXN], st[MAXN];
    int fin[MAXN], depth[MAXN];

    int nc, suff, pos;
    /// nc -> node count
    /// suff -> Index of the node denoting the longest palindromic proper
                /// suffix of the current prefix

    void init() {
        str[0] = -1;
        nc = 2; suff = 2;
        len[1] = -1, link[1] = 1;
        len[2] =  0, link[2] = 1;
        CLR(ed[1]), CLR(ed[2]);
        occ[1] = occ[2] = 0;
    }

    inline int scale(char c) { return c-'a'; }

    inline int nextLink(int cur) {
        while (str[pos - 1 - len[cur]] != str[pos]) cur = link[cur];
        return cur;
    }

    inline bool addLetter(int p) {
        pos = p;
        int let = scale(str[pos]);
        int cur = nextLink(suff);

        if (ed[cur][let]) {
            suff = ed[cur][let];
            fin[pos] = depth[suff];
            occ[suff]++;
            return false;
        }

        suff = ++nc;
        CLR(ed[nc]);
        len[nc] = len[cur] + 2;
        ed[cur][let] = nc;
        occ[nc] = 1;

        if (len[nc] == 1) {
            st[nc] = pos;
            link[nc] = 2;
            fin[pos] = depth[nc] = 1;
            return true;
        }
        link[nc] = ed[nextLink(link[cur])][let];
        fin[pos] = depth[nc] = depth[link[nc]] + 1;
        st[nc] = pos-len[nc] + 1;
        return true;
    }

    void build(int _n) {
        n = _n;
        init();
        for(int i=1;i<=n;i++) addLetter(i);
        for(int i=nc;i>=3;i--) occ[link[i]] += occ[i];
        occ[2] = occ[1] = 0;
    }

    void printTree() {
        puts(str);
        cout << "Node\tStart\tLength\tOcc\n";
        for(int i=3;i<=nc;i++) {
            cout << i << "\t" << st[i] << "\t" << len[i] << "\t" << occ[i] << "\n";
        }
    }
}

int main() {
    scanf("%s",pt::str+1);
    pt::build(strlen(pt::str+1));
    return 0;
}

