#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <functional>

#define MAXN 1000

using namespace std;

typedef long double ld;

pair<int, int> rh[MAXN];

ld dp[MAXN + 1][MAXN];

int main() {
  int t; scanf("%d\n", &t);
  for(int tc = 1; tc <= t; tc++) {
    int n, k; scanf("%d %d\n", &n, &k);
    for(int i = 0; i < n; i++)
      scanf("%d %d\n", &rh[i].first, &rh[i].second);

    sort(rh, rh + n, greater<pair<int, int>>());
    memset(dp, 0, sizeof(dp));

    for(int i = 0; i < n; i++) {
      memcpy(dp[i + 1], dp[i], sizeof(dp[i]));
      dp[i + 1][1] = max(
        dp[i + 1][1],
        M_PI * pow((ld) rh[i].first, 2) +
          2 * M_PI * (ld) rh[i].first * rh[i].second);

      for(int j = 1; j < k; j++) {
        dp[i + 1][j + 1] = max(
          dp[i + 1][j + 1],
          dp[i][j] + 2 * M_PI * rh[i].first * rh[i].second);
      }
    }
    printf("Case #%d: %.9Lf\n", tc, dp[n][k]);
  }
  return 0;
}
