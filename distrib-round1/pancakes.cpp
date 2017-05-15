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

#include "pancakes.h"
#include "message.h"

#define MAXN 2000
#define INF 0x3f3f3f3f

using namespace std;

typedef long long ll;
typedef long double ld;

int main() {
  int nodeBegin = (int) (MyNodeId() * GetStackSize() / NumberOfNodes());
  int nodeEnd = (int) ((MyNodeId() + 1) * GetStackSize() / NumberOfNodes());

  ll cnt = 0;
  for(int i = nodeBegin; i < nodeEnd; i++) {
    if(GetStackItem(i) < (i == 0 ? 0 : GetStackItem(i - 1))) cnt++;
  }

  if(MyNodeId() != 0) {
    PutLL(0, cnt); Send(0);
  } else {
    for(int k = 1; k < NumberOfNodes(); k++) {
      Receive(k); cnt += GetLL(k);
    }
    printf("%lld\n", cnt + 1);
  }
  return 0;
}
