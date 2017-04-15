#include <cstdio>
#include <cstring>

#define MAXN 25

using namespace std;

char grid[MAXN][MAXN];

char start[MAXN];

int main() {
  int t; scanf("%d\n", &t);
  for(int tc = 1; tc <= t; tc++) {
    int r, c; scanf("%d %d\n", &r, &c);

    memset(start, 0, sizeof(start));
    for(int i = 0; i < r; i++) {
      for(int j = 0; j < c; j++) {
        scanf("%c", &grid[i][j]);
        if(!start[i] && grid[i][j] != '?') start[i] = grid[i][j];
      }
      scanf("\n");
    }

    int lastRow = 0;
    for(int i = 0; i < r; i++) {
      char curr = start[i];
      if(!curr) continue;

      lastRow = i;
      for(int j = 0; j < c; j++) {
        if(grid[i][j] == '?') grid[i][j] = curr;
        else curr = grid[i][j];
      }
      for(int i2 = i - 1; i2 >= 0 && !start[i2]; i2--) {
        memcpy(grid[i2], grid[i], sizeof(grid[i]));
      }
    }
    for(int i = lastRow + 1; i < r; i++) {
      memcpy(grid[i], grid[lastRow], sizeof(grid[lastRow]));
    }

    printf("Case #%d:\n", tc);
    for(int i = 0; i < r; i++) {
      for(int j = 0; j < c; j++) {
        printf("%c", grid[i][j]);
      }
      printf("\n");
    }
  }
  return 0;
}
