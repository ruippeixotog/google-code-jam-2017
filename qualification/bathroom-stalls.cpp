#include <cstdio>
#include <map>

using namespace std;

typedef long long ll;

map<ll, ll> spaces;

int main() {
  int t; scanf("%d\n", &t);
  for(int tc = 1; tc <= t; tc++) {
    ll n, k; scanf("%lld %lld\n", &n, &k);
    spaces.clear();
    spaces[n]++;

    ll ls = -1, rs = -1;
    while(k > 0) {
      auto it = prev(spaces.end());
      ll size = it->first, count = it->second;
      spaces.erase(it);

      ls = (size - 1) / 2;
      rs = size / 2;
      spaces[ls] += count;
      spaces[rs] += count;
      k -= count;
    }
    printf("Case #%d: %lld %lld\n", tc, max(ls, rs), min(ls, rs));
  }
  return 0;
}
