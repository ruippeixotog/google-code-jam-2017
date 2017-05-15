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

#include "weird_editor.h"
#include "message.h"

#define MAXN 2000
#define MOD 1000000007

using namespace std;

typedef long long ll;
typedef long double ld;

//int hist[10];

inline ll madd(ll a, ll b) { return (a + b) % MOD; }
inline ll mmul(ll a, ll b) { return (a * b) % MOD; }

ll mpow(ll a, ll p) {
  if(p == 0) return 1;
  ll halfPow = mpow(a, p / 2);
  return mmul(halfPow, p % 2 ? mmul(a, halfPow) : halfPow);
}

void search(int digit) {
  Receive(0);
  ll from = GetLL(0);
//  cerr << "search " << digit << " from " << from << endl;

  int nodeBegin = (int) (from + MyNodeId() * (GetNumberLength() - from) / NumberOfNodes());
  int nodeEnd = (int) (from + (MyNodeId() + 1) * (GetNumberLength() - from) / NumberOfNodes());

  int cnt = 0; ll last = -1;
  for(int i = nodeBegin; i < nodeEnd; i++) {
    if(GetDigit(i) == digit) {
//      cerr << "found " << digit << " at " << i << endl;
      cnt++; last = i;
    }
  }
  PutInt(0, cnt); PutLL(0, last); Send(0);
}

void calcMod() {
  Receive(0);
  ll from = GetLL(0), to = GetLL(0);

  int nodeBegin = (int) (from + MyNodeId() * (to - from) / NumberOfNodes());
  int nodeEnd = (int) (from + (MyNodeId() + 1) * (to - from) / NumberOfNodes());

//  if(nodeBegin != nodeEnd) cerr << "calc " << nodeBegin << " to " << nodeEnd << endl;

  ll currMult = mpow(10, nodeBegin), sum = 0;
  for(int i = nodeBegin; i < nodeEnd; i++) {
    sum = madd(sum, currMult);
    currMult = mmul(currMult, 10);
  }
//  if(nodeBegin != nodeEnd) cerr << "calc res " << sum << endl;
  PutLL(0, sum); Send(0);
}

int main() {
  if(MyNodeId() != 0) {
    for(int d = 9; d > 0; d--) {
      search(d);
      calcMod();
    }
  } else {
    ll res = 0, cnt = 0, from = 0;

    for(int d = 9; d > 0; d--) {
      for(int k = 0; k < NumberOfNodes(); k++) {
        PutLL(k, from); Send(k);
      }
      search(d);

      ll multTo = GetNumberLength() - cnt;
      for(int k = 0; k < NumberOfNodes(); k++) {
        Receive(k);
        cnt += GetInt(k);
        ll lastK = GetLL(k);
        if(lastK != -1) from = lastK + 1;
      }

      ll multFrom = GetNumberLength() - cnt;

//      cerr << " digit " << d << ": " << multFrom << " - " << multTo << endl;
      for(int k = 0; k < NumberOfNodes(); k++) {
        PutLL(k, multFrom); PutLL(k, multTo); Send(k);
      }
      calcMod();

      for(int k = 0; k < NumberOfNodes(); k++) {
        Receive(k);
        res = madd(res, mmul(d, GetLL(k)));
      }
//      cerr << "curr " << res << endl;
    }
    printf("%lld\n", res);
  }
  return 0;
}
