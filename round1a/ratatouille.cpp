#include <algorithm>
#include <cstdio>
#include <cstring>

#define MAXN 50
#define MAXP 50

using namespace std;

int r[MAXN], q[MAXN][MAXP];

int compare(int provided, int needed) {
  int margin = needed / 10;
  return provided < needed - margin ? -1 :
    provided > needed + margin ? 1 : 0;
}

int main() {
  int t; scanf("%d\n", &t);
  for(int tc = 1; tc <= t; tc++) {
    int n, p; scanf("%d %d\n", &n, &p);
    for(int i = 0; i < n; i++)
      scanf("%d", &r[i]);

    for(int i = 0; i < n; i++) {
      for(int j = 0; j < p; j++) {
        scanf("%d", &q[i][j]);
      }
      sort(q[i], q[i] + p);
    }

    int idx[MAXN];
    memset(idx, 0, sizeof(idx));

    int currSize = 1, cnt = 0;
    while(true) {
      bool found = true, finished = false;

      for(int i = 0; i < n; i++) {
        int cmp;
        while(idx[i] < p && (cmp = compare(q[i][idx[i]], r[i] * currSize)) < 0) {
          idx[i]++;
        }

        if(idx[i] == p) { finished = true; break; }
        if(cmp > 0) { found = false; break; }
      }

      if(finished) break;
      if(!found) currSize++;
      else {
        cnt++;
        for(int i = 0; i < n; i++) idx[i]++;
      }
    }
    printf("Case #%d: %d\n", tc, cnt);
  }
  return 0;
}
