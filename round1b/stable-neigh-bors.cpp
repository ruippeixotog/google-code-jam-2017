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
#include <cassert>

#define MAXN 2000
#define INF 1000000000

using namespace std;

typedef long long ll;
typedef long double ld;

int n, ryb[3], gvo[3];

char rybCh[3] = {'R', 'Y', 'B'};
char gvoCh[3] = {'G', 'V', 'O'};

string calc() {
  string res = "";

  ryb[0] -= gvo[0]; ryb[1] -= gvo[1]; ryb[2] -= gvo[2];
  if(ryb[0] < 0 || ryb[1] < 0 || ryb[2] < 0) return res;

  // special case
  if(ryb[0] == 0 && ryb[1] == 0 && ryb[2] == 0) {
    if((gvo[0] > 0) + (gvo[1] > 0) + (gvo[2] > 0) == 1) {
      for(int i = 0; i < 3; i++) {
        while(gvo[i] > 0) {
          res.push_back(rybCh[i]);
          res.push_back(gvoCh[i]);
          gvo[i]--;
        }
      }
      return res;
    }
  }

  int firsti = -1, lasti = -1;
  while(res.size() < n) {
    int maxi = -1, maxv = 0;
    if(firsti >= 0 && firsti != lasti && ryb[firsti] > maxv) { maxi = firsti; maxv = ryb[firsti]; }
    for(int i = 0; i < 3; i++) {
      if(i != lasti && ryb[i] > maxv) { maxi = i; maxv = ryb[i]; }
    }
    if(maxi == -1) return "";

    res.push_back(rybCh[maxi]);
    ryb[maxi]--;
    while(gvo[maxi] > 0) {
      res.push_back(gvoCh[maxi]);
      res.push_back(rybCh[maxi]);
      gvo[maxi]--;
    }
    if(firsti < 0) firsti = maxi;
    lasti = maxi;
  }
  if(res[0] == res[res.size() - 1]) {
    return "";
  }
  return res;
}

int main() {
  int t; scanf("%d\n", &t);
  for(int tc = 1; tc <= t; tc++) {
    scanf("%d %d %d %d %d %d %d\n",
          &n, &ryb[0], &gvo[2], &ryb[1], &gvo[0], &ryb[2], &gvo[1]);

    string res = calc();
    printf("Case #%d: %s\n", tc, res.empty() ? "IMPOSSIBLE" : res.c_str());
  }
  return 0;
}
