#include <algorithm>
#include <cstdio>

#define MAXN 1000

using namespace std;

typedef long double ld;

pair<int, int> ks[MAXN];

ld ts[MAXN + 1];

int main() {
  int t; scanf("%d\n", &t);
  for(int tc = 1; tc <= t; tc++) {
    int d, n; scanf("%d %d\n", &d, &n);
    for(int i = 0; i < n; i++)
      scanf("%d %d\n", &ks[i].first, &ks[i].second);

    sort(ks, ks + n);
    ts[n] = 0.0;
    for(int i = n - 1; i >= 0; i--) {
      ts[i] = max((d - ks[i].first) / (ld) ks[i].second, ts[i + 1]);
    }
    printf("Case #%d: %.9Lf\n", tc, d / ts[0]);
  }
  return 0;
}
