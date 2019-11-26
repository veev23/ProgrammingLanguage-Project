#pragma once
#ifndef BIGINTNERUALNET_H
#define BIGINTNERUALNET_H
#include "bigint.h"
#define MAX_NODES 4
#define LAYER_CNT 2
class BigIntNerualNet {
	//layer[i][j] : i번째 레이어, j번째 노드
	bigint layer[LAYER_CNT][MAX_NODES];
	bigint output;
	//weight[l][i][j] : l번째 레이어에서 l+1번째 레이어간의 weight, i -> j
	bigint weight[LAYER_CNT - 1][MAX_NODES][MAX_NODES];
	//output으로 이어지는 간선의 weight
	bigint last_weight[MAX_NODES];
	void InitNNTest();
	void FeedForwardTest();
public:
	BigIntNerualNet();
	void InitNN();
	void FeedForward();
	void ShowResult();
};
#endif