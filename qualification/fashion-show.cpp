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

using namespace std;

int n;
bool row[MAXN], col[MAXN], diag1[MAXN * 2 - 1], diag2[MAXN * 2 - 1];

vector<pair<pair<int, int>, char>> crossSol, plusSol;

void placeCrosses() {
  crossSol.clear();

  for(int i = 0; i < n; i++) {
    if(row[i]) continue;
    for(int j = 0; j < n; j++) {
      if(col[j]) continue;

      crossSol.push_back({{i, j}, 'x'});
      col[j] = true;
      break;
    }
  }
}

void placePluses() {
  plusSol.clear();

  vector<int> ds;
  for(int i = 0; i < n - 1; i++) {
    ds.push_back(i);
    ds.push_back(n * 2 - i - 2);
  }
  ds.push_back(n - 1);

  for(int d: ds) {
    if(diag1[d]) continue;
    int i = d < n ? d : n - 1;
    int j = d < n ? 0 : d - n + 1;

    for(; i >= 0 && j < n; i--, j++) {
      if(diag2[i - j + n - 1]) continue;

      plusSol.push_back({{i, j}, '+'});
      diag2[i - j + n - 1] = true;
      break;
    }
  }

//  vector<pair<int, int>> ds;
//  for(int d = 0; d < n * 2 - 1; d++) {
//    int i = d < n ? d : n - 1;
//    int j = d < n ? 0 : d - n + 1;
//
//    int count = 0, all = 0;
//    for(; i >= 0 && j < n; i--, j++) {
//      all++;
//      count += !diag2[i - j + n - 1];
//    }
//    cerr << "d = " << d << "; size = " << all << "; av = " << count << endl;
//    ds.push_back({count, d});
//  }
//  sort(ds.begin(), ds.end());
//
//  for(auto d: ds) {
//    cerr << "running " << d.second << endl;
//    if(diag1[d.second]) continue;
//    int i = d.second < n ? d.second : n - 1;
//    int j = d.second < n ? 0 : d.second - n + 1;
//
//    for(; i >= 0 && j < n; i--, j++) {
//      if(diag2[i - j + n - 1]) continue;
//
//      plusSol.push_back({{i, j}, '+'});
//      diag2[i - j + n - 1] = true;
//      break;
//    }
//  }
}

int main() {
  int t; scanf("%d\n", &t);
  for(int tc = 1; tc <= t; tc++) {
    int m; scanf("%d %d\n", &n, &m);

    cerr << "case " << tc << endl;
    cerr << "case " << n << " " << m << endl;

//    memset(row, 0, sizeof(row) + sizeof(col) + sizeof(diag1) + sizeof(diag2));
    memset(row, 0, sizeof(row));
    memset(col, 0, sizeof(col));
    memset(diag1, 0, sizeof(diag1));
    memset(diag2, 0, sizeof(diag2));

    int initPoints = 0;
    for(int i = 0; i < m; i++) {
      char ch; int r, c; scanf("%c %d %d\n", &ch, &r, &c);
      r--; c--;
      if(ch == 'x' || ch == 'o') row[r] = col[c] = true;
      if(ch == '+' || ch == 'o') diag1[r + c] = diag2[r - c + n - 1] = true;
      initPoints += ch == '.' ? 0 : ch == 'o' ? 2 : 1;
    }

    placeCrosses();
    placePluses();

//    cerr << "SOL(x)" << endl;
//    for(int i = 0; i < crossSol.size(); i++) {
//      cerr << crossSol[i].first.first << "," << crossSol[i].first.second << endl;
//    }

    vector<pair<pair<int, int>, char>> sol;
    sort(plusSol.begin(), plusSol.end());

//    cerr << "SOL(+)" << endl;
//    for(int i = 0; i < plusSol.size(); i++) {
//      cerr << plusSol[i].first.first << "," << plusSol[i].first.second << endl;
//    }

    merge(crossSol.begin(), crossSol.end(), plusSol.begin(), plusSol.end(), back_inserter(sol));

//    cerr << "SOL" << endl;
//    for(int i = 0; i < sol.size(); i++) {
//      cerr << get<0>(sol[i]) << "," << get<1>(sol[i]) << endl;
//    }

    int oCount = 0;
    for(int i = 1; i < sol.size(); i++) {
      if(sol[i].first == sol[i - 1].first) oCount++;
    }

    printf("Case #%d: %d %d\n", tc,
           initPoints + (int) crossSol.size() + (int) plusSol.size(),
           (int) sol.size() - oCount);

    for(int i = 0; i < sol.size(); i++) {
      if(i < sol.size() - 1 && sol[i].first == sol[i + 1].first) {
        printf("o %d %d\n", sol[i].first.first + 1, sol[i].first.second + 1);
        i++;
      } else {
        printf("%c %d %d\n", sol[i].second,
               sol[i].first.first + 1, sol[i].first.second + 1);
      }
    }
  }
  return 0;
}
