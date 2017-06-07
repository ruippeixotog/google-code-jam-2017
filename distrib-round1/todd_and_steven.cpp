#include <cstdio>
#include <utility>
#include <tuple>

#include "todd_and_steven.h"
#include "message.h"

#define MOD 1000000007

using namespace std;

typedef long long ll;

inline ll madd(ll a, ll b) { return (a + b) % MOD; }
inline ll mmul(ll a, ll b) { return (a * b) % MOD; }

int tv, tvEnd, sv, svEnd;

int svSearch(ll tvIdx) {
  if(tvIdx == GetToddLength()) return (int) GetStevenLength();
  ll tvVal = GetToddValue(tvIdx);

  int begin = 0, end = (int) GetStevenLength();
  while(begin < end) {
    int mid = (begin + end) / 2;
    if(GetStevenValue(mid) < tvVal) begin = mid + 1;
    else end = mid;
  }
  return begin;
}

pair<int, int> search(ll k) {
  int tvBegin = 0, tvEnd = (int) GetToddLength();
  while(tvBegin < tvEnd) {
    int tvMid = (tvBegin + tvEnd) / 2;
    int svIdx = svSearch(tvMid);

    if(tvMid + svIdx == k) return {tvMid, svIdx};
    if(tvMid + svIdx < k) tvBegin = tvMid + 1;
    else tvEnd = tvMid;
  }
  return {tvBegin, k - tvBegin};
}

void setWork() {
  ll arrLength = GetStevenLength() + GetToddLength();
  ll nodeBegin = MyNodeId() * arrLength / NumberOfNodes();
  ll nodeEnd = (MyNodeId() + 1) * arrLength / NumberOfNodes();

  tie(tv, sv) = search(nodeBegin);
  tie(tvEnd, svEnd) = search(nodeEnd);
}

int main() {
  setWork();

  ll sum = 0;
  while(tv < tvEnd || sv < svEnd) {
    if(tv < tvEnd && (sv == svEnd || GetToddValue(tv) < GetStevenValue(sv))) {
      sum = madd(sum, GetToddValue(tv) ^ (tv + sv));
      tv++;
    } else {
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
