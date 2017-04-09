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

#define MAXN 2000
#define INF 1000000000

using namespace std;

typedef long long ll;
typedef long double ld;

int main() {
  int t; scanf("%d\n", &t);
  for(int tc = 1; tc <= t; tc++) {
    string n; cin >> n;

    for(int i = n.length() - 1; i > 0; i--) {
      if(n[i] >= n[i - 1]) continue;
      n[i - 1]--;
      for(int j = i; j < n.length(); j++) n[j] = '9';
    }

    printf("Case #%d: %lld\n", tc, stoll(n));
  }
  return 0;
}
