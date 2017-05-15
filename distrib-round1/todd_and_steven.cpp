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

#define MAXN 2000
#define INF 0x3f3f3f3f
#define MOD 1000000007

using namespace std;

typedef long long ll;
typedef long double ld;

inline ll madd(ll a, ll b) { return (a + b) % MOD; }
inline ll mmul(ll a, ll b) { return (a * b) % MOD; }

int searchTv(int tv0, int tv1, ll v) {
  int begin = tv0, end = tv1;
  while(begin < end) {
    int mid = (begin + end) / 2;
    if(GetToddValue(mid) < v) begin = mid + 1;
    else end = mid;
  }
  return begin;
}

int searchSv(int sv0, int sv1, ll v) {
  int begin = sv0, end = sv1;
  while(begin < end) {
    int mid = (begin + end) / 2;
    if(GetStevenValue(mid) < v) begin = mid + 1;
    else end = mid;
  }
  return begin;
}

void splitWork(int beginNode, int endNode, int tv0, int tv1, int sv0, int sv1) {
  if(beginNode == endNode - 1) {
    cerr << "node " << beginNode << ": " << tv0 << "-" << tv1 << ", " << sv0 << "-" << sv1 << endl;
    PutInt(beginNode, tv0); PutInt(beginNode, tv1);
    PutInt(beginNode, sv0); PutInt(beginNode, sv1);
    Send(beginNode);

  } else {
    if((tv1 - tv0) == 0 && (sv1 - sv0) == 0) {
      for(int i = beginNode; i < endNode; i++)
        splitWork(beginNode, beginNode + 1, tv0, tv1, sv0, sv1);
    } else {
      cerr << "work for nodes " << beginNode << "-" << endNode << ": " << tv0 << "-" << tv1 << ", " << sv0 << "-" << sv1 << endl;
      int midNode = (beginNode + endNode) / 2;
      int tvMid, svMid;
      if((tv1 - tv0) > (sv1 - sv0)) {
        tvMid = (tv0 + tv1) / 2;
        svMid = searchSv(sv0, sv1, GetToddValue(tvMid));
//        cerr << "  * tvMid = " << GetToddValue(tvMid) << endl;
//        cerr << "  * svMid = " << GetStevenValue(svMid) << endl;
      } else {
        svMid = (sv0 + sv1) / 2;
        tvMid = searchTv(tv0, tv1, GetStevenValue(svMid));
//        cerr << "  * svMid = " << GetStevenValue(svMid) << endl;
//        cerr << "  * tvMid = " << GetToddValue(tvMid) << endl;
      }
      splitWork(beginNode, midNode, tv0, tvMid, sv0, svMid);
      splitWork(midNode, endNode, tvMid, tv1, svMid, sv1);
    }
  }
}

int main() {
  if(MyNodeId() == 0) {
    splitWork(0, NumberOfNodes(),
              0, (int) GetToddLength(), 0, (int) GetStevenLength());

//    cerr << "all sent" << endl;
  }

  Receive(0);
  int tv0 = GetInt(0), tv1 = GetInt(0), sv0 = GetInt(0), sv1 = GetInt(0);

//  if(tv0 < tv1 || sv0 < sv1) {
//    cerr << "node " << MyNodeId() << ": " << tv0 << "-" << tv1 << ", " << sv0 << "-" << sv1 << endl;
//  }

  ll sum = 0;
  int tvi = tv0, svi = sv0;
  while(tvi < tv1 || svi < sv1) {
    if(tvi < tv1 && (svi == sv1 || GetToddValue(tvi) < GetStevenValue(svi))) {
      cerr << "at position " << (tvi + svi) << ": " << GetToddValue(tvi) << endl;
      sum = madd(sum, GetToddValue(tvi) ^ (tvi + svi));
      tvi++;
    } else {
      cerr << "at position " << (tvi + svi) << ": " << GetStevenValue(svi) << endl;
      sum = madd(sum, GetStevenValue(svi) ^ (tvi + svi));
      svi++;
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
