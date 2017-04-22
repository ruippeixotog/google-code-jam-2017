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
#include <climits>
#include <cfloat>

#define MAXN 2000
#define INF 1000000000

using namespace std;

typedef long long ll;
typedef long double ld;

int e[MAXN], s[MAXN];
int d[MAXN][MAXN];
int u[MAXN], v[MAXN];

ld tDist[MAXN][MAXN];

int main() {
  int t; scanf("%d\n", &t);
  for(int tc = 1; tc <= t; tc++) {
    int n, q; scanf("%d %d\n", &n, &q);
    for(int i = 0; i < n; i++)
      scanf("%d %d\n", &e[i], &s[i]);
    for(int i = 0; i < n; i++) {
      for(int j = 0; j < n; j++) {
        scanf("%d", &d[i][j]);
        if(d[i][j] == -1) d[i][j] = 0x3f3f3f3f;
      }
      d[i][i] = 0;
    }
    for(int i = 0; i < q; i++)
      scanf("%d %d\n", &u[i], &v[i]);

    for(int k = 0; k < n; k++) {
      for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
          if(d[i][j] > d[i][k] + d[k][j])
            d[i][j] = d[i][k] + d[k][j];
        }
      }
    }

//    for(int i = 0; i < n; i++) {
//      for(int j = 0; j < n; j++) {
//        cerr << d[i][j] << " ";
//      }
//      cerr << endl;
//    }
//    cerr << endl;

    for(int i = 0; i < n; i++) {
      for(int j = 0; j < n; j++) {
        tDist[i][j] = LDBL_MAX / 3;
        if(e[i] >= d[i][j]) {
          tDist[i][j] = d[i][j] / (ld) s[i];
        } else {
          tDist[i][j] = LDBL_MAX / 3;
        }
      }
    }

//    for(int i = 0; i < n; i++) {
//      for(int j = 0; j < n; j++) {
//        cerr << tDist[i][j] << " ";
//      }
//      cerr << endl;
//    }
//    cerr << endl;

    for(int k = 0; k < n; k++) {
      for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
          if(tDist[i][j] > tDist[i][k] + tDist[k][j])
            tDist[i][j] = tDist[i][k] + tDist[k][j];
        }
      }
    }


//    for(int i = 0; i < n; i++) {
//      for(int j = 0; j < n; j++) {
//        cerr << tDist[i][j] << " ";
//      }
//      cerr << endl;
//    }
//    cerr << endl;

    printf("Case #%d:", tc);
    for(int i = 0; i < q; i++) {
      printf(" %.9Lf", tDist[u[i] - 1][v[i] - 1]);
    }
    printf("\n");
  }
  return 0;
}
