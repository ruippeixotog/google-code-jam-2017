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

#include "query_of_death.h"
#include "message.h"

#define MAXN 2000
#define INF 0x3f3f3f3f

using namespace std;

typedef long long ll;
typedef long double ld;

int qodNode, qod, qodValue;

ll getSum(int nodeId) {
  int nodeBegin = (int) (nodeId * GetLength() / NumberOfNodes());
  int nodeEnd = (int) ((nodeId + 1) * GetLength() / NumberOfNodes());

  ll sum = 0;
  for(int i = nodeBegin; i < nodeEnd; i++) {
    if(qod == i) sum += qodValue;
    else if(qod != -1) sum += GetValue(i);
    else {
      int realVal = (int) GetValue(i);
      for(int k = 0; k < 75; k++) {
        if(GetValue(i) != realVal) {
          qod = i; qodValue = realVal;
          return -1;
        }
      }
      sum += realVal;
    }
  }
  return sum;
}

int main() {
  qod = -1;

  ll sum = getSum(MyNodeId());
  if(sum == -1) { PutLL(0, -1); PutInt(0, qod); PutInt(0, qodValue); }
  else PutLL(0, sum);
  Send(0);

  if(MyNodeId() == 0) {
    sum = 0;
    for(int k = 0; k < NumberOfNodes(); k++) {
      Receive(k);
      ll sumK = GetLL(k);
      if(sumK == -1) { qodNode = k; qod = GetInt(k); qodValue = GetInt(k); }
      else sum += sumK;
    }
    for(int k = 0; k < NumberOfNodes(); k++) {
      PutInt(k, qodNode); PutInt(k, qod); PutInt(k, qodValue);
      Send(k);
    }
  }

  Receive(0);
  qodNode = GetInt(0);
  qod = GetInt(0), qodValue = GetInt(0);
  if(MyNodeId() == (qodNode + 1) % NumberOfNodes()) {
    PutLL(0, getSum(qodNode));
    Send(0);
  }

  if(MyNodeId() == 0) {
    Receive((qodNode + 1) % NumberOfNodes());
    sum += GetLL((qodNode + 1) % NumberOfNodes());
    printf("%lld\n", sum);
  }
  return 0;
}
