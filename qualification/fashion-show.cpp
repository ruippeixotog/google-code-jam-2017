#include <cstdio>
#include <cstring>
#include <vector>

#define MAXN 100

using namespace std;

int n;
bool row[MAXN], col[MAXN], diag1[MAXN * 2 - 1], diag2[MAXN * 2 - 1];

int crossSol[MAXN][MAXN], plusSol[MAXN][MAXN];

void placeCrosses() {
  for(int i = 0; i < n; i++) {
    if(row[i]) continue;
    for(int j = 0; j < n; j++) {
      if(col[j]) continue;

      crossSol[i][j] = 1;
      col[j] = true;
      break;
    }
  }
}

int placePluses() {
  vector<int> ds;
  for(int i = 0; i < n - 1; i++) {
    ds.push_back(i);
    ds.push_back(n * 2 - i - 2);
  }
  ds.push_back(n - 1);

  int points = 0;
  for(int d: ds) {
    if(diag1[d]) { points++; continue; }
    int i = d < n ? d : n - 1;
    int j = d < n ? 0 : d - n + 1;

    for(; i >= 0 && j < n; i--, j++) {
      if(diag2[i - j + n - 1]) continue;

      plusSol[i][j] = 1;
      diag2[i - j + n - 1] = true;
      points++;
      break;
    }
  }
  return points;
}

int main() {
  int t; scanf("%d\n", &t);
  for(int tc = 1; tc <= t; tc++) {
    int m; scanf("%d %d\n", &n, &m);

    memset(row, 0, sizeof(row));
    memset(col, 0, sizeof(col));
    memset(diag1, 0, sizeof(diag1));
    memset(diag2, 0, sizeof(diag2));
    memset(crossSol, 0, sizeof(crossSol));
    memset(plusSol, 0, sizeof(plusSol));

    for(int i = 0; i < m; i++) {
      char ch; int r, c; scanf("%c %d %d\n", &ch, &r, &c);
      r--; c--;
      if(ch != '+') {
        crossSol[r][c] = -1;
        row[r] = col[c] = true;
      }
      if(ch != 'x') {
        plusSol[r][c] = -1;
        diag1[r + c] = diag2[r - c + n - 1] = true;
      }
    }

    placeCrosses();
    int plusPoints = placePluses();

    int pieces = 0;
    for(int i = 0; i < n; i++) {
      for(int j = 0; j < n; j++) {
        if(crossSol[i][j] > 0 || plusSol[i][j] > 0) pieces++;
      }
    }

    printf("Case #%d: %d %d\n", tc, n + plusPoints, pieces);
    for(int i = 0; i < n; i++) {
      for(int j = 0; j < n; j++) {
        if(crossSol[i][j] > 0 || plusSol[i][j] > 0) {
          char ch = crossSol[i][j] ? (plusSol[i][j] ? 'o' : 'x') : '+';
          printf("%c %d %d\n", ch, i + 1, j + 1);
        }
      }
    }
  }
  return 0;
}
