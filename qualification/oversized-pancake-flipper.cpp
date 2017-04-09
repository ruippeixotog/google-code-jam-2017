#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

int main() {
  int t; scanf("%d\n", &t);
  for(int tc = 1; tc <= t; tc++) {
    string str; int k;
    cin >> str >> k;

    int cnt = 0;
    for(int i = 0; i <= str.length() - k; i++) {
      if(str[i] == '+') continue;
      for(int j = 0; j < k; j++) {
        str[i + j] = str[i + j] == '-' ? '+' : '-';
      }
      cnt++;
    }

    for(int i = (int) str.length() - k + 1; i < str.length(); i++) {
      if(str[i] == '-') { cnt = -1; break; }
    }

    printf("Case #%d: ", tc);
    if(cnt >= 0) printf("%d\n", cnt);
    else printf("IMPOSSIBLE\n");
  }
  return 0;
}
