#include <algorithm>
#include <cstdio>
#include <cstring>

#define MAXN 50

using namespace std;

typedef long double ld;

int n, k;
ld u, p[MAXN];

ld uCurr, pCurr[MAXN];
ld dp[MAXN + 1][MAXN + 1];

int main() {
  int t; scanf("%d\n", &t);
  for(int tc = 1; tc <= t; tc++) {
    scanf("%d %d\n", &n, &k);
    scanf("%Lf\n", &u);
    for(int i = 0; i < n; i++)
      scanf("%Lf", &p[i]);

    sort(p, p + n);

    ld best = 0.0;
    for(int i0 = 0; i0 < n; i0++) {
      uCurr = u;
      memcpy(pCurr, p, sizeof(p));

      for(int i = i0; i < n; i++) {
        ld nextP = i == n - 1 ? 1.0 : pCurr[i + 1];
        ld toTrain = min(uCurr, (nextP - pCurr[i]) * (i - i0 + 1));
        uCurr -= toTrain;

        for(int j = i0; j <= i; j++) {
          pCurr[j] += toTrain / (i - i0 + 1);
        }
      }
      if(i0 > 0) {
        pCurr[i0 - 1] = min(pCurr[i0 - 1] + uCurr, (ld) 1.0);
      }

      memset(dp, 0, sizeof(dp));
      dp[0][0] = 1.0;
      for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
          dp[i + 1][j] = dp[i + 1][j] + dp[i][j] * (1.0 - pCurr[i]);
          dp[i + 1][j + 1] = dp[i + 1][j + 1] + dp[i][j] * pCurr[i];
        }
      }

      ld res = 0.0;
      for(int i = k; i <= n; i++) {
        res += dp[n][i];
      }
      best = max(best, res);
    }

    printf("Case #%d: %.9Lf\n", tc, best);
  }
  return 0;
}
