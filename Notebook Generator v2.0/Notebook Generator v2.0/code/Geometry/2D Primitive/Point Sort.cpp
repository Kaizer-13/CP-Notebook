// sort the points in counterclockwise order that starts from the half line x≤0,y=0.
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair <ll, ll> point;

#define x first
#define y second

int main() {
  int n; cin >> n;
  vector <point> p(n);
  for (auto &it : p) scanf("%lld %lld", &it.x, &it.y);
  sort(p.begin(), p.end(), [] (point a, point b) {
    return atan2l(a.y, a.x) < atan2l(b.y, b.x);
  });
  for (auto it : p) printf("%lld %lld\n", it.x, it.y);
  return 0;
}