#include <cstdio>

#include "query_of_death.h"
#include "message.h"

#define MAX_NODES 100

typedef long long ll;

bool broken[MAX_NODES];

ll getSum(int begin, int end) {
  ll sum = 0;
  for(int i = begin; i < end; i++) {
    sum += GetValue(i);
  }
  if(end - begin >= 2) {
    for(int k = 0; k < 100; k++) {
      int first = (int) GetValue(begin);
      if(GetValue(begin) != first) return -1;
    }
  }
  return sum;
}

void mainMaster() {
  int nodeCount = NumberOfNodes() - 1;
  ll min = 0, max = GetLength(), sum = 0;

  while(min != -1) {
    int nodeId = 0;
    for(int k = 1; k < NumberOfNodes(); k++) {
      if(!broken[k]) {
        PutInt(k, nodeId++); PutInt(k, nodeCount); PutLL(k, min); PutLL(k, max);
        Send(k);
      }
    }

    min = max = -1;
    for(int k = 1; k < NumberOfNodes(); k++) {
      if(!broken[k]) {
        Receive(k);
        int nodeBegin = GetInt(k), nodeEnd = GetInt(k); ll part = GetLL(k);
        if(part >= 0) sum += part;
        else {
          broken[k] = true;
          min = nodeBegin; max = nodeEnd;
          nodeCount--;
        }
      }
    }
  }
  for(int k = 1; k < NumberOfNodes(); k++) {
    if(!broken[k]) { PutInt(k, -1); Send(k); }
  }
  printf("%lld\n", sum);
}

void mainSlave() {
  ll sum = 0;
  while(sum >= 0) {
    Receive(0);
    int nodeId = GetInt(0);
    if(nodeId == -1) break;

    int nodeCount = GetInt(0); ll min = GetLL(0), max = GetLL(0);

    int nodeBegin = (int) (min + nodeId * (max - min) / nodeCount);
    int nodeEnd = (int) (min + (nodeId + 1) * (max - min) / nodeCount);
    sum = getSum(nodeBegin, nodeEnd);

    PutInt(0, nodeBegin); PutInt(0, nodeEnd); PutLL(0, sum);
    Send(0);
  }
}

int main() {
  MyNodeId() == 0 ? mainMaster() : mainSlave();
  return 0;
}
