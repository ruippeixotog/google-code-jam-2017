#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

int main() {
  int t; scanf("%d\n", &t);
  for(int tc = 1; tc <= t; tc++) {
    string n; cin >> n;

    for(int i = (int) n.length() - 1; i > 0; i--) {
      if(n[i] >= n[i - 1]) continue;
      n[i - 1]--;
      for(int j = i; j < n.length(); j++) {
        n[j] = '9';
      }
    }
    printf("Case #%d: %lld\n", tc, stoll(n));
  }
  return 0;
}
