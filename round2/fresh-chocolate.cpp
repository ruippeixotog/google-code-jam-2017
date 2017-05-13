#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>

#define MAXN 100
#define INF 0x3f3f3f3f

using namespace std;

typedef long long ll;
typedef long double ld;

int n, g[4];

int dp[MAXN + 1][MAXN + 1][MAXN + 1];

int dp3() {
  memset(dp[0], 0x3f, sizeof(dp[0]));
  dp[0][g[1]][g[2]] = 0;

  for(int i = n; i >= 0; i--) {
    for(int j = n; j >= 0; j--) {
      if(i >= 1 && j >= 1) {
        dp[0][i - 1][j - 1] = min(dp[0][i - 1][j - 1], dp[0][i][j] + 1);
      }
      if(i >= 3) {
        dp[0][i - 3][j] = min(dp[0][i - 3][j], dp[0][i][j] + 2);
      }
      if(j >= 3) {
        dp[0][i][j - 3] = min(dp[0][i][j - 3], dp[0][i][j] + 2);
      }
    }
  }
  return min(dp[0][0][0], min(
    min(dp[0][1][0], dp[0][2][0] + 1),
    min(dp[0][0][1], dp[0][0][2] + 1)));
}

int dp4() {
  memset(dp, 0x3f, sizeof(dp));
  dp[g[1]][g[2]][g[3]] = 0;

  for(int i = n; i >= 0; i--) {
    for(int j = n; j >= 0; j--) {
      for(int k = n; k >= 0; k--) {
        if(i >= 1 && k >= 1) {
          dp[i - 1][j][k - 1] = min(dp[i - 1][j][k - 1], dp[i][j][k] + 1);
        }
        if(j >= 2) {
          dp[i][j - 2][k] = min(dp[i][j - 2][k], dp[i][j][k] + 1);
        }
        if(i >= 2 && j >= 1) {
          dp[i - 2][j - 1][k] = min(dp[i - 2][j - 1][k], dp[i][j][k] + 2);
        }
        if(j >= 1 && k >= 2) {
          dp[i][j - 1][k - 2] = min(dp[i][j - 1][k - 2], dp[i][j][k] + 2);
        }
        if(i >= 4) {
          dp[i - 4][j][k] = min(dp[i - 4][j][k], dp[i][j][k] + 3);
        }
        if(k >= 4) {
          dp[i][j][k - 4] = min(dp[i][j][k - 4], dp[i][j][k] + 3);
        }
      }
    }
  }
  return min(dp[0][0][0], min(min(
    min(dp[1][0][0], min(dp[2][0][0] + 1, dp[3][0][0] + 2)),
    min(dp[0][0][1], min(dp[0][0][2] + 1, dp[0][0][3] + 2))),
    min(dp[0][1][0], min(dp[1][1][0] + 1, dp[0][1][1] + 1))));
}

int main() {
  int t; scanf("%d\n", &t);
  for(int tc = 1; tc <= t; tc++) {
    int p; scanf("%d %d\n", &n, &p);

    memset(g, 0, sizeof(g));
    for(int i = 0; i < n; i++) {
      int gi; scanf("%d", &gi);
      g[gi % p]++;
    }

    int res = -1;
    switch(p) {
      case 2: res = g[1] / 2; break;
      case 3: res = dp3(); break;
      case 4: res = dp4(); break;
    }
    printf("Case #%d: %d\n", tc, n - res);
  }
  return 0;
}
