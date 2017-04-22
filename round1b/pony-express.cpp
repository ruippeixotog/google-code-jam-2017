#include <cstdio>
#include <cfloat>

#define MAXN 100
#define INF 0x3f3f3f3f

typedef long double ld;

int e[MAXN], s[MAXN], d[MAXN][MAXN], u[MAXN], v[MAXN];

ld timeTo[MAXN][MAXN];

template<typename T> void floyd(int n, T dist[MAXN][MAXN]) {
  for(int k = 0; k < n; k++) {
    for(int i = 0; i < n; i++) {
      for(int j = 0; j < n; j++) {
        if(dist[i][j] > dist[i][k] + dist[k][j])
          dist[i][j] = dist[i][k] + dist[k][j];
      }
    }
  }
}

int main() {
  int t; scanf("%d\n", &t);
  for(int tc = 1; tc <= t; tc++) {
    int n, q; scanf("%d %d\n", &n, &q);
    for(int i = 0; i < n; i++) {
      scanf("%d %d\n", &e[i], &s[i]);
    }
    for(int i = 0; i < n; i++) {
      for(int j = 0; j < n; j++) {
        scanf("%d", &d[i][j]);
        if(d[i][j] == -1) d[i][j] = INF;
      }
      d[i][i] = 0;
    }
    for(int i = 0; i < q; i++) {
      scanf("%d %d\n", &u[i], &v[i]);
    }

    floyd(n, d);
    for(int i = 0; i < n; i++) {
      for(int j = 0; j < n; j++) {
        timeTo[i][j] = e[i] >= d[i][j] ? d[i][j] / (ld) s[i] : LDBL_MAX / 2;
      }
    }
    floyd(n, timeTo);

    printf("Case #%d:", tc);
    for(int i = 0; i < q; i++) {
      printf(" %.9Lf", timeTo[u[i] - 1][v[i] - 1]);
    }
    printf("\n");
  }
  return 0;
}
