#include <algorithm>
#include <cstdio>
#include <cstring>

#include "weird_editor.h"
#include "message.h"

#define MOD 1000000007

using namespace std;

typedef long long ll;

inline ll madd(ll a, ll b) { return (a + b) % MOD; }
inline ll mmul(ll a, ll b) { return (a * b) % MOD; }

ll mpow(ll a, ll p) {
  if(p == 0) return 1;
  ll halfPow = mpow(a, p / 2);
  return mmul(halfPow, p % 2 ? mmul(a, halfPow) : halfPow);
}

int digitCnt[10];

void search() {
  int nodeBegin = (int) (MyNodeId() * GetNumberLength() / NumberOfNodes());
  int nodeEnd = (int) ((MyNodeId() + 1) * GetNumberLength() / NumberOfNodes());

  for(int i = nodeBegin; i < nodeEnd; i++) {
    int digit = (int) GetDigit(i);
    for(int d = 1; d < digit; d++) digitCnt[d] = 0;
    digitCnt[digit]++;
  }
  for(int d = 9; d > 0; d--) {
    PutInt(0, digitCnt[d]);
  }
  Send(0);
}

void calcMod() {
  Receive(0);
  ll digitCntAll = 0;
  for(int i = 9; i > 0; i--) {
    digitCnt[i] = GetInt(0);
    digitCntAll += digitCnt[i];
  }
  int zerosCnt = (int) (GetNumberLength() - digitCntAll);

  int nodeBegin = (int) (MyNodeId() * digitCntAll / NumberOfNodes());
  int nodeEnd = (int) ((MyNodeId() + 1) * digitCntAll / NumberOfNodes());

  ll currMult = mpow(10, zerosCnt + nodeBegin), sum = 0;
  int curr = 0;
  for(int d = 1; d < 10; d++) {
    if(curr < nodeBegin) {
      int toPass = min(digitCnt[d], nodeBegin - curr);
      digitCnt[d] -= toPass;
      curr += toPass;
    }
    while(curr < nodeEnd && digitCnt[d]) {
      sum = madd(sum, mmul(d, currMult));
      currMult = mmul(currMult, 10);
      digitCnt[d]--; curr++;
    }
  }
  PutLL(0, sum); Send(0);
}

int main() {
  search();

  if(MyNodeId() == 0) {
    memset(digitCnt, 0, sizeof(digitCnt));
    for(int k = 0; k < NumberOfNodes(); k++) {
      Receive(k);
      for(int d = 9; d > 0; d--) {
        int cnt = GetInt(k);
        if(cnt > 0) {
          for(int d2 = 1; d2 < d; d2++) digitCnt[d2] = 0;
          digitCnt[d] += cnt;
        }
      }
    }

    for(int k = 0; k < NumberOfNodes(); k++) {
      for(int d = 9; d > 0; d--) {
        PutInt(k, digitCnt[d]);
      }
      Send(k);
    }
  }

  calcMod();

  if(MyNodeId() == 0) {
    ll res = 0;
    for(int k = 0; k < NumberOfNodes(); k++) {
      Receive(k);
      res = madd(res, GetLL(k));
    }
    printf("%lld\n", res);
  }
  return 0;
}
