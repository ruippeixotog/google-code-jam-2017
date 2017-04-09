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

#define MAXN 1000000

using namespace std;

typedef long long ll;
typedef long double ld;

map<int, int> spaces;

int main() {
  int t; scanf("%d\n", &t);
  for(int tc = 1; tc <= t; tc++) {
    int n, k; scanf("%d %d\n", &n, &k);
    spaces.clear();
    spaces[n]++;

    int ls = -1, rs = -1;
    for(int i = 0; i < k; i++) {
      auto it = prev(spaces.end());

      int size = it->first;
      ls = (size - 1) / 2;
      rs = size / 2;

      if(it->second == 1) spaces.erase(it);
      else it->second--;

      spaces[ls]++;
      spaces[rs]++;
    }
    printf("Case #%d: %d %d\n", tc, max(ls, rs), min(ls, rs));
  }
  return 0;
}
