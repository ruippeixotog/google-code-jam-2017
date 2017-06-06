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

#include "todd_and_steven.h"
#include "message.h"

#define MOD 1000000007

using namespace std;

typedef long long ll;
typedef long double ld;

inline ll madd(ll a, ll b) { return (a + b) % MOD; }
inline ll mmul(ll a, ll b) { return (a * b) % MOD; }

int search(int begin, int end, ll (*getValue)(ll), ll toFind) {
  while(begin < end) {
    int mid = (begin + end) / 2;
    if(getValue(mid) < toFind) begin = mid + 1;
    else end = mid;
  }
  return begin;
}

void splitWork(int beginNode, int endNode, int tv0, int tv1, int sv0, int sv1) {
  if(beginNode == endNode - 1) {
//    cerr << "node " << beginNode << ": " << tv0 << "-" << tv1 << ", " << sv0 << "-" << sv1 << endl;
    PutInt(beginNode, tv0); PutInt(beginNode, tv1);
    PutInt(beginNode, sv0); PutInt(beginNode, sv1);
    Send(beginNode);
    return;
  }
  int tvMid, svMid;
  if((tv1 - tv0) > (sv1 - sv0)) {
    tvMid = (tv0 + tv1) / 2;
    svMid = search(sv0, sv1, GetStevenValue, GetToddValue(tvMid));
  } else {
    svMid = (sv0 + sv1) / 2;
    tvMid = search(tv0, tv1, GetToddValue, GetStevenValue(svMid));
  }

  int weight = (int) ((endNode - beginNode) *
    (ll) ((tvMid - tv0) + (svMid - sv0)) / ((tv1 - tv0) + (sv1 - sv0)));

  int midNode = min(beginNode + 1, max(endNode - 1, beginNode + weight));
  splitWork(beginNode, midNode, tv0, tvMid, sv0, svMid);
  splitWork(midNode, endNode, tvMid, tv1, svMid, sv1);
}

int main() {
  if(MyNodeId() == 0) {
    splitWork(0, NumberOfNodes(),
              0, (int) GetToddLength(), 0, (int) GetStevenLength());
  }

  Receive(0);
  int tv = GetInt(0), tvEnd = GetInt(0), sv = GetInt(0), svEnd = GetInt(0);

  ll sum = 0;
  while(tv < tvEnd || sv < svEnd) {
    if(tv < tvEnd && (sv == svEnd || GetToddValue(tv) < GetStevenValue(sv))) {
//      cerr << "at position " << (tv + sv) << ": " << GetToddValue(tv) << endl;
      sum = madd(sum, GetToddValue(tv) ^ (tv + sv));
      tv++;
    } else {
//      cerr << "at position " << (tv + sv) << ": " << GetStevenValue(sv) << endl;
      sum = madd(sum, GetStevenValue(sv) ^ (tv + sv));
      sv++;
    }
  }
  PutLL(0, sum);
  Send(0);

  if(MyNodeId() == 0) {
    sum = 0;
    for(int k = 0; k < NumberOfNodes(); k++) {
      Receive(k); sum = madd(sum, GetLL(k));
    }
    printf("%lld\n", sum);
  }
  return 0;
}
