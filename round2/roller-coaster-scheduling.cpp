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

#define MAXN 1000
#define INF 0x3f3f3f3f

using namespace std;

typedef long long ll;
typedef long double ld;

int hist[2][MAXN];

int main() {
  int t; scanf("%d\n", &t);
  for(int tc = 1; tc <= t; tc++) {
    int n, c, m; scanf("%d %d %d\n", &n, &c, &m);

    memset(hist, 0, sizeof(hist));
    for(int i = 0; i < m; i++) {
      int p, b; scanf("%d %d\n", &p, &b);
      hist[--b][--p]++;
    }

    vector<int> conflicts;
    for(int i = 0; i < n; i++) {
      if(hist[0][i] > 0 || hist[1][i] > 0) cerr << "elems " << hist[0][i] << " " << hist[1][i] << " " << endl;

      if(hist[0][i] > 0 && hist[1][i] > 0) {
//        cerr << "conf at " << (i + 1) << " " << endl;
        conflicts.push_back(i);
      }
    }

    int rides = 0, upgrades = 0;
    for(int i = 0; i < conflicts.size(); i++) {
      int ci = conflicts[i];

      int confs = min(hist[0][ci], hist[1][ci]);
      hist[0][ci] -= confs;
      hist[1][ci] -= confs;

      cerr << "confs pos " << (ci + 1) << " " << confs << endl;

      for(int j = i + 1; confs > 0 && j < conflicts.size(); j++) {
        int cj = conflicts[j];
        int rd = min(confs, min(hist[0][cj], hist[1][cj])) * 2;
        if(rd > 0) cerr << "conf*conf rides: " << rd << endl;
        rides += rd;
        confs -= rd / 2;
        hist[0][cj] -= rd / 2;
        hist[1][cj] -= rd / 2;
      }
      if(hist[1][ci] <= hist[0][ci]) {
        for(int j = 0; confs > 0 && j < n; j++) {
          if(j == ci) continue;
          int rd = min(confs, hist[0][j]);
          if(rd > 0) cerr << "conf*r0 rides: " << rd << endl;
          rides += rd;
          confs -= rd;
          hist[0][j] -= rd;
          hist[0][ci] += rd;
        }
      }
      if(hist[0][ci] <= hist[1][ci]) {
        for (int j = 0; confs > 0 && j < n; j++) {
          if (j == ci) continue;
          int rd = min(confs, hist[1][j]);
          if (rd > 0) cerr << "conf*r1 rides: " << rd << endl;
          rides += rd;
          confs -= rd;
          hist[1][j] -= rd;
          hist[1][ci] += rd;
        }
      }
      if(confs > 0) {
        cerr << "left conf rides: " << (confs * 2) << endl;
        if(ci == 0) rides += confs * 2;
        else { rides += confs; upgrades += confs; }
      }
    }
    int free1 = 0, free2 = 0;
    for(int i = 0; i < n; i++) {
      free1 += hist[0][i];
      free2 += hist[1][i];
    }
    cerr << free1 << " " << free2 << endl;
    rides += max(free1, free2);

    printf("Case #%d: %d %d\n", tc, rides, upgrades);
  }
  return 0;
}
