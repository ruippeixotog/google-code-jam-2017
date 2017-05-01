#include <algorithm>
#include <cstdio>
#include <cstring>
#include <tuple>

#define MAXAC 100
#define MAXAJ 100

using namespace std;

tuple<int, int, int> act[MAXAC + MAXAJ + 2];

int dp[MAXAC + MAXAJ + 2][2][721];

int main() {
  int t; scanf("%d\n", &t);
  for(int tc = 1; tc <= t; tc++) {
    int ac, aj; scanf("%d %d\n", &ac, &aj);
    for(int i = 0; i < ac; i++) {
      get<2>(act[i]) = 0;
      scanf("%d %d\n", &get<0>(act[i]), &get<1>(act[i]));
    }
    for(int i = 0; i < aj; i++) {
      get<2>(act[ac + i]) = 1;
      scanf("%d %d\n", &get<0>(act[ac + i]), &get<1>(act[ac + i]));
    }

    act[ac + aj] = {0, 0, -1};
    act[ac + aj + 1] = {1440, 1440, -1};
    sort(act, act + ac + aj + 2);

    memset(dp, 0x3f, sizeof(dp));
    dp[0][0][0] = dp[0][1][0] = 0;

    for(int i = 1; i < ac + aj + 2; i++) {
      for(int st = 0; st < 2; st++) {
        int c0, d0, c1, d1, isJ0, isJ1;
        tie(c0, d0, isJ0) = act[i - 1];
        tie(c1, d1, isJ1) = act[i];
        if(isJ0 == -1) isJ0 = st;
        if(isJ1 == -1) isJ1 = st;

        int task = isJ1 ? d1 - c1 : 0;
        for(int mc = 0; mc <= 720; mc++) {
          for(int mc1 = 0; mc1 <= c1 - d0 && mc + mc1 + task <= 720; mc1++) {
            int exchanges = isJ0 != isJ1 ? 1 :
              isJ0 && isJ1 ? (mc1 == c1 - d0 ? 0 : 2) :
              mc1 == 0 ? 0 : 2;

              dp[i][st][mc + mc1 + task] = min(
                dp[i][st][mc + mc1 + task], dp[i - 1][st][mc] + exchanges);
          }
        }
      }
    }

    int res = min(dp[ac + aj + 1][0][720], dp[ac + aj + 1][1][720]);
    printf("Case #%d: %d\n", tc, res);
  }
  return 0;
}
