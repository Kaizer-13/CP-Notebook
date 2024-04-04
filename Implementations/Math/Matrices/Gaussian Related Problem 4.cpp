/***
Problem :
Given an array ara[] of n integers, you will be given some queries.
? L x --> How many subsequences of ara[1:L] has XOR-sum = x

Solution 1:
Let dp[i][x] be the number of subsequences of the first i elements with xor x.
Let's prove that dp[i][x] is equal for all x belonging to the set!
Let's assume this holds true for i-1 and see what happens in the transition to i.
Notice that it holds true for i=0. Let j be the value that dp[i-1][x] is equal to
for all x belonging to the set. If a[i] is in the set, and x is in the set,
(x^a[i]) is in the set. Therefore, dp[i-1][x]=j and  which makes dp[i][x]=2*j for all x in the set.
Notice that the set doesn't change so dp[i][x]=0 for all x that aren't in the set.
If a[i] isn't in the set, we have 3 cases for x. If x is in the set,  isn't in the set.
Therefore, dp[i][x]=j+0=j. If x is to be added to the set in this step, is in the set.
Therefore, dp[i][x]=0+j=j. Otherwise, dp[i][x]=0.

Solution 2:
Let's suppose we have the basis vectors for the elements upto L.

ans is 0 if, x is not representable by the basis vectors.
Otherwise, ans for any query upto L is = 2 ^ (L-S)
S -> size of basis

***/

// solution1
#include <bits/stdc++.h>
using namespace std;
const int MOD = 1000000007;
const int MAX = 100010;
vector<pair<int,int> > v[MAX];
int arr[MAX], res[MAX];
vector<int> s;
bool b[1<<20];
int main() {
    int n, q, L, x;
    cin >> n >> q;
    for (int i=0;i<n;i++) cin >> ara[i];
    for (int i=0;i<q;i++) {
        cin >> L >> x;
        v[L-1].push_back({x,i});
    }
    s.push_back(0);
    b[0]=1;
    int ans=1;
    for (int i=0;i<n;i++) {
        if (b[arr[i]]) ans = (ans + ans) % MOD;
        else {
            int tmp=s.size();
            for (int x=0;x<tmp;x++) {
                s.push_back(s[x]^arr[i]);
                b[s.back()]=1;
            }
        }
        for (int x=0;x<v[i].size();x++)
        res[v[i][x].second] = ans * b[v[i][x].first];
    }
    for (int i=0;i<q;i++) cout << res[i] << endl;
    return 0;
}

